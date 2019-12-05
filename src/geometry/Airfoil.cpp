/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <memory>
#include <string>

#include "Airfoil.h"
#include "Axis.h"
#include "ComponentBase.h"
#include "DeHallerCriterion.h"
#include "Deviation.h"
#include "Error.h"
#include "InputObjectBase.h"
#include "Line.h"
#include "Point.h"
#include "ProfileGenerator.h"
#include "Rotate.h"
#include "Scale.h"
#include "Spline.h"
#include "Translate.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Airfoil::computeProfile()					// <- this guy
{
	// initialize working value
	double bladeOutletAngle {get("fluidOutletAngle")};

	do
	{
		store
		(
			"bladeOutletAngle",	// [deg]
			bladeOutletAngle
		);

		// generate a new profile
		generator_->generate
		(
			get("bladeInletAngle") - get("bladeOutletAngle")
		);
		store
		(
			"maxCamber",			// [-] - % of span
			generator_->get("maxCamber")
		);
		store
		(
			"maxCamberPosition",	// [-] - % of span
			generator_->get("maxCamberPosition")
		);

		bladeOutletAngle = get("fluidOutletAngle") - deviation_->compute(*this);
	}
	while
	(
		!isEqual(bladeOutletAngle, get("bladeOutletAngle"))
	);

	store
	(
		"stagger",					// [deg]
		get("bladeInletAngle") - generator_->get("leadingInclination")
	);
}


double Airfoil::computeBladeInletAngle() const
{
	return computeFluidInletAngle() - get("incidence");
}


double Airfoil::computeDeltaP() const
{
	double phi
	{
		get("bladeVelocity") / get("axialVelocity")
	};
	double k
	{
		0.5 * get("density") * std::pow(get("axialVelocity"), 2)
	};
	double deltaP
	{
		k * (std::pow(phi, 2) - 1)
	};

	// set to realizable if we haven't got one
	if (!hasKey("deltaP"))
	{
		// check global deltaP
		if (get("deltaP") < deltaP)
			deltaP = get("deltaP");
	}
	// compute regularly otherwise
	else
	{
		double tanBeta
		{
			std::tan(degToRad(get("fluidOutletAngle")))
		};
		deltaP += k * std::pow(tanBeta, 2);
	}

	return deltaP;
}


double Airfoil::computeFluidInletAngle() const
{
	return radToDeg
	(
		std::atan(get("bladeVelocity") / get("axialVelocity"))
	);
}


double Airfoil::computeFluidOutletAngle() const
{
	// if we're the first or the only airfoil
	// we don't have the swirl constant
	if
	(
		isEqual(get("radius"), get("hubRadius")) ||
		isEqual(get("numberOfStations"), 1.0)
	)
		return eulerEquation();

	return vortexEquation();
}


double Airfoil::eulerEquation() const
{
	double phi
	{
		get("bladeVelocity") / get("axialVelocity")
	};
	double k
	{
		0.5 * get("density") * std::pow(get("axialVelocity"), 2)
	};
	double tanBeta
	{
		std::sqrt
		(
			std::pow(phi, 2) - get("deltaP") / k - 1.0
		)
	};

	return radToDeg(std::atan(tanBeta));
}


void Airfoil::initializePointers(const Stringmap<>& input)
{
	generator_.reset
	(
		new ProfileGenerator {input}
	);
	deviation_.reset
	(
		new Deviation {input}
	);
}


void Airfoil::generatePoints() noexcept
{
	points_.clear();

	for (const auto& p : *generator_)
		points_.push_back
		(
			std::make_unique<Point>(p)
		);
}


void Airfoil::generateLines() noexcept
{
	std::vector<Point> points;
	for (const auto& p : points_)
		points.push_back(*p);

	surface_.reset
	(
		new Spline {points}
	);
	trailing_.reset
	(
		new Line
		{
			getLowerTrailingEdge(),
			getUpperTrailingEdge()
		}
	);
}


double Airfoil::limitAngle(const double angle) const noexcept
{
	double angleNew {angle};

	if (angleNew < 0.0)
		angleNew = 0.0;
	else if (angleNew > 90.0)
		angleNew = 90.0;
	
	return angleNew;
}


void Airfoil::positionProfile() const
{
	Rotate rotate {};
	Scale scale {};
	Translate translate {};

	// scale to chord
	scale.setParameters
	(
		getCenter(),
		get("chord")
	);
	scale.manipulate(*this);

	// stack
	translate.setParameters
	(
		getCenter(),
		Point {0, 0, get("radius")}
	);
	translate.manipulate(*this);

	// rotate
	rotate.setParameters
	(
		degToRad(get("stagger"))
	);
	rotate.manipulate(*this);
}


double Airfoil::vortexEquation() const
{
	double ratio
	{
		get("radius") / get("hubRadius")
	};
	double swirl
	{
		get("swirl") * std::pow(ratio, get("vortexLawExponent"))
	};
	double tanBeta
	{
		(get("bladeVelocity") - swirl) / get("axialVelocity")
	};

	return radToDeg(std::atan(tanBeta));
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Airfoil::buildInputMap() noexcept
{
	store("incidence",	0.0);	// [deg]
	store("solidity",	NAN);	// [-]
}


void Airfoil::check() const
{
	if (hasValue("solidity"))
		if
		(
			isLessOrEqual(get("solidity"), 0.0)
		)
			THROW_RUNTIME_ERROR("value of keyword 'solidity' <= 0");
}


void Airfoil::computeAndStore()
{
	// we store the some values locally
	// because they change with radius
	store
	(
		"deltaP",			// [Pa]
		computeDeltaP()
	);
	store
	(
		"pitch",			// [m]
		get("pitch")
	);
	store
	(
		"radius",			// [m]
		get("radius")
	);

	store
	(
		"fluidInletAngle",	// [deg]
		limitAngle(computeFluidInletAngle())
	);
	store
	(
		"fluidOutletAngle",	// [deg]
		limitAngle(computeFluidOutletAngle())
	);
	store
	(
		"bladeInletAngle",	// [deg]
		computeBladeInletAngle()
	);
	store
	(
		"bladeOutletAngle",	// [deg]
		NAN					// dummy
	);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Airfoil::Airfoil
(
	const Stringmap<>& input,
	const ComponentBase& owner
)
:
	wrapped_ {false}
{
	owner_ = &owner;
	buildInputMap();
	addOptional
	(
		"incidence",
		"solidity"
	);
	parse(input);
	check();

	initializePointers(input);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Airfoil::build()
{
	computeAndStore();

	// apply diffusion criterion						// <- this guy
	DeHallerCriterion deHaller {};
	store
	(
		"fluidOutletAngle",		// [deg]
		deHaller
		(
			get("fluidInletAngle"),
			get("fluidOutletAngle")
		)
	);

	// recompute because fluid angles may have changed
	computeDeltaP();

	store
	(
		"chord",				// [m]
		get("solidity") * get("pitch")
	);

	computeProfile();
	generatePoints();
	positionProfile();

	generateLines();
}


double Airfoil::computeSwirl() const
{
	double tanBeta
	{
		std::tan(degToRad(get("fluidOutletAngle")))
	};

	return get("bladeVelocity") - get("axialVelocity") * tanBeta;
}


Vectorpair<int> Airfoil::getDimTags() const noexcept
{
	Vectorpair<int> dimTags;

	for (const auto& p : points_)
		dimTags.push_back
		(
			p->getDimTag()
		);

	return std::move(dimTags);
}


Point Airfoil::getCenter() const noexcept
{
	if (points_.empty())
		return Point::origin();

	PointCoordinates point {};
	PointCoordinates sum {Point::origin().getCoordinates()};
	int count {0};

	for (const auto& p : points_)
	{
		point = p->getCoordinates();

		sum[Axis::X] += point[Axis::X];
		sum[Axis::Y] += point[Axis::Y];
		sum[Axis::Z] += point[Axis::Z];
		
		count++;
	}

	for (auto& s : sum)
		s /= static_cast<double>(count);

	return Point
	{
		sum[Axis::X],
		sum[Axis::Y],
		sum[Axis::Z]
	};
}


Point Airfoil::getLeadingEdge() const
{
	if (points_.empty())
		THROW_RUNTIME_ERROR("airfoil not built");

	// we always have an odd number of points
	int size {static_cast<int>(points_.size())};
	int pos
	{
		(size - 1) / 2
	};

	// LE is always in the middle
	return *points_[pos + 1];
}


Point Airfoil::getLowerTrailingEdge() const
{
	if (points_.empty())
		THROW_RUNTIME_ERROR("airfoil not built");

	// lower TE is always at the end
	return *points_.back();
}


Point Airfoil::getUpperTrailingEdge() const
{
	if (points_.empty())
		THROW_RUNTIME_ERROR("airfoil not built");

	// upper TE is always at the beginning
	return *points_.front();
}


bool Airfoil::isWrapped() const noexcept
{
	return wrapped_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
