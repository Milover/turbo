/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <utility>

#include "ProfileHexMeshGenerator.h"

#include "General.h"
#include "Geometry.h"
#include "GeometryInterface.h"
#include "Profile.h"
#include "Utility.h"
#include "Variables.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

std::vector<MeshGeneratorBase::Point> inletOutletSegment
(
	const Point& point,
	const Vector& camberDirection,
	const Vector& inwardNormal
) const noexcept
{
	double alpha
	{
		pi - angleBetween(camberDirection, inwardNormal)
	};
	double l	// bezier polygon segment length
	{
		chord_.value() / (1.0 + std::cos(alpha))
	};

	std::vector<Point> points;

	points.push_back(point);		// polygon start point
	points.emplace_back				// polygon central point
	(
		point + camberDirection * l
	);
	points.emplace_back				// polygon end point
	(
		point + (camberDirection - inwardNormal) * l
	);

	return points;
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

Sptrvector<geometry::Curve> ProfileHexMeshGenerator::constructBoundary
(
	const design::Profile& profile
) const
{
	auto translate = []
	(
		const Vector& translation,
		Pointvector& points
	) -> void
	{
		for (auto& p : points)
			p += translation;
	};

	// designate a bunch of curves (curve pointers) as transfinite
	auto makeTransfinite = [&]
	(
		auto&& self,
		const interface::GmshTransfinite::Distribution& distribution,
		auto&& first,
		auto&&... rest
	) -> void
	{
		if constexpr (sizeof...(rest) != 0)
		{
			makeTransfinite
			(
				makeTransfinite,
				distribution,
				std::forward<decltype(rest)>(rest)...
			);
		}

		Float factor;

		if constexpr (distribution == interface::GmshTransfinite::PROGRESSION)
		{
			factor = progFactor_;
		}
		else
		{
			factor = bumpFactor_;	// XXX: this should probably be adjustable
		}

		interface::GmshTransfinite {}
		(
			std::forward<decltype(first)>(first),
			distribution,
			discretization_,
			factor
		);
	};

	// create
	Pointvector camberTop
	{
		profile.camberLine()
	};
	Pointvector inPerTop
	{
		inletOutletSegment
		(
			profile.lePoint(),
			profile.leDirection(),
			Vector::zAxis()
		)
	};
	Pointvector outPerTop
	{
		inletOutletSegment
		(
			profile.tePoint(),
			profile.teDirection(),
			-Vector::zAxis()
		)
	};

	// copy
	Pointvector camberBot {camberTop};
	Pointvector inPerBot {inPerTop};
	Pointvector outPerBot {outPerTop};

	// because the points are currently on the midline of the section
	Vector translation {0.0, pitch_.value() / 2.0};

	// translate
	translate( translation, camberTop);
	translate( translation, inPerTop);
	translate( translation, outPerTop);
	translate(-translation, camberBot);
	translate(-translation, inPerBot);
	translate(-translation, outPerBot);

	// construct
	gometry::Bezier inPerTop_g
	{
		std::move(inPerTop)
	};
	gometry::Bezier outPerTop_g
	{
		std::move(outPerTop)
	};
	gometry::Spline camberTop_g
	{
		inPerTop_g.startSptr(),
		std::move(camberTop),
		outPerTop_g.startSptr()
	};

	gometry::Bezier inPerBot_g
	{
		std::move(inPerBot)
	};
	gometry::Bezier outPerBot_g
	{
		std::move(outPerBot)
	};
	gometry::Spline camberBot_g
	{
		inPerBot_g.startSptr(),
		std::move(camberBot),
		outPerBot_g.startSptr()
	};

	geometry::Line inlet_g
	{
		inPerTop_g.endSptr(),
		inPerBot_g.endSptr()
	};
	geometry::Line outlet_g
	{
		outPerTop_g.endSptr(),
		outPerBot_g.endSptr()
	};

	// make transfinite
	makeTransfinite
	(
		makeTransfinite,		// because it's recursive
		interface::GmshTransfinite::PROGRESSION,
		&inPerTop_g,
		&outPerTop_g,
		&inPerBot_g,
		&outPerTop_g,
	);
	makeTransfinite
	(
		makeTransfinite,		// because it's recursive
		interface::GmshTransfinite::BUMP,
		&camberTop_g,
		&camberBot_g,
		&inlet_g,
		&outlet_g,
	);

	// set names
	// FIXME: physical groups not implemented

	// store
	Sptrvector<Curve> boundary;

	boundary.emplace_back(std::move(inlet_g));
	boundary.emplace_back(std::move(inPerTop_g));
	boundary.emplace_back(std::move(camberTop_g));
	boundary.emplace_back(std::move(outPerTop_g));
	boundary.emplace_back(std::move(outlet_g));
	boundary.emplace_back(std::move(outPerBot_g));
	boundary.emplace_back(std::move(camberBot_g));
	boundary.emplace_back(std::move(inPerBot_g));

	return boundary;
}


Sptr<geometry::Surface> ProfileHexMeshGenerator::constructSection
(
	const Sptrvector<geometry::Curve>& curves
) const
{
	geometry::PlanarSurface surface {std::move(boundary)};

	surface.storeCorners
	(
		std::move(curves[0]->startSptr()),		// inlet start point
		std::move(curves[0]->endSptr()),		// inlet end point
		std::move(curves[4]->endSptr())			// outlet end point
		std::move(curves[4]->startSptr()),		// outlet start point
	);

	// set names
	// FIXME: physical groups not implemented

	interface::GmshTransfinite {}(&surface);
	interface::GmshRecombine {}(&surface);
	interface::GmshSmooth {}
	(
		&surface,
		smootherIter_.value()
	);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ProfileHexMeshGenerator::ProfileHexMeshGenerator
(
	const input::Chord& chord,
	const input::NumberOfCamber& discretization,
	const input::Pitch& pitch
)
:
	MeshGeneratorBase
	{
		chord,
		discretization,
		pitch
	},
	smootherIter
	{
		input::read<input::SmootherIter>()
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Uptr<geometry::Volume> ProfileHexMeshGenerator::generate
(
	const design::Profile& profile
) const
{
	Uptr<geometry::Volume> mesh
	{
		std::make_unique<geometry::Volume>
		(
			operators::Extrude {}
			(
				constructSection
				(
					constructBoundary(profile)
				),
				-Vector::zAxis()	// (-) to avoid having to flip the base normal
			)
		)
	};

	geometry::interface::GmshGenerate();

	return mesh;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
