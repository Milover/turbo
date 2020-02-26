/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <iostream>
#include "gmsh.h"

#include "Airfoil.h"
#include "Blade.h"
#include "ComponentBase.h"
#include "Error.h"
#include "InputObjectBase.h"
#include "SurfaceFilling.h"
#include "SurfaceSection.h"
#include "Utility.h"
#include "Wire.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Blade::buildAirfoils()
{
	for (auto& a : airfoils_)
	{
		computeAndStore();

		a->build();

		// we store the swirl constant only once
		if (station_ == 0)
			store
			(
				"swirl",
				a->computeSwirl()
			);

		station_++;
	}
}


void Blade::buildSurfaces() noexcept	// TODO: implement properly
{
	std::vector<Wire> contour;
	std::vector<Wire> trailing;

	for (const auto& a : airfoils_)
	{
		contour.emplace_back
		(
			std::move(a->profile.getContour())
		);
		trailing.emplace_back
		(
			std::move(a->profile.getTrailingEdge())
		);

		if (&a == &airfoils_.front())
		{
			bottom_.reset
			(
				new SurfaceFilling
				{
					std::move
					(
						Wire
						{
							a->profile.getContour(),
							a->profile.getTrailingEdge()
						}
					)
				}
			);
		}
		else if (&a == &airfoils_.back())
		{
			top_.reset
			(
				new SurfaceFilling
				{
					std::move
					(
						Wire
						{
							a->profile.getContour(),
							a->profile.getTrailingEdge()
						}
					)
				}
			);
		}
	}

	contour_.reset
	(
		new SurfaceSection
		{
			std::move(contour)
		}
	);
	trailing_.reset
	(
		new SurfaceSection
		{
			std::move(trailing)
		}
	);
}


void Blade::checkNumberOfStations() const
{
	if (numberOfStations_ == 0)
		THROW_RUNTIME_ERROR("number of stations == 0");
}


void Blade::checkOffsets() const		// NOTE: disabled until tip/root profile
										//		 extrapolation is implemented
{
/*
	double offsets
	{
		get("hubOffset") + get("tipOffset")
	};

	if
	(
		isLessOrEqual(get("span"), offsets)
	)
		THROW_RUNTIME_ERROR("offsets larger than span");
*/
	if
	(
		!isEqual(get("hubOffset"), 0.0) ||
		!isEqual(get("tipOffset"), 0.0)
	)
		THROW_RUNTIME_ERROR("station offsetting not implemented, set offsets to 0");
}


double Blade::computeBladeVelocity() const
{
	double radius {computeRadius()};

	return pi * get("rpm") * radius / 30.0;
}


double Blade::computePitch() const
{
	double radius {computeRadius()};

	return 2.0 * pi * radius / get("numberOfBlades");
}


double Blade::computeRadius() const
{
	double workingSpan
	{
		get("span") - get("hubOffset") - get("tipOffset")
	};

	if (numberOfStations_ == 1)
		return get("hubRadius") + get("hubOffset") + 0.5 * workingSpan;

	double stationOffset
	{
		workingSpan / (static_cast<double>(numberOfStations_ - 1))
	};

	return get("hubRadius") + get("hubOffset") +
		static_cast<double>(station_) * stationOffset;
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Blade::buildInputMap() noexcept
{
	store("hubOffset",			0.0);	// [m]
	store("tipOffset",			0.0);	// [m]
	store("vortexLawExponent",	-1.0);	// [-]
}


void Blade::check() const
{
	for (const auto& [key, value] : this->inputMap_)
	{
		if (key == "vortexLawExponent")
			continue;
		else if (value < 0.0)
			THROW_RUNTIME_ERROR("value of keyword '" + key + "' < 0");
	}
	
	checkNumberOfStations();
}


void Blade::computeAndStore()
{
	// because we recompute during building
	// for each station
	store
	(
		"bladeVelocity",		// [m s-1]
		computeBladeVelocity()
	);
	store
	(
		"pitch",				// [m]
		computePitch()
	);
	store
	(
		"radius",				// [m]
		computeRadius()
	);
}


void Blade::parse(const Stringmap<>& input)
{
	InputObjectBase::parse(input);

	auto search {input.find("numberOfStations")};

	if (search != input.end())
	{
		try
		{
			numberOfStations_ = std::stoi(search->second);
			store
			(
				"numberOfStations",
				static_cast<double>(numberOfStations_)
			);
		}
		catch (...)
		{
			THROW_ARGUMENT_ERROR("can't convert '" + search->second + "' to int");
		}
	}
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Blade::Blade
(
	const Stringmap<>& input,
	const ComponentBase& owner
)
:
	station_ {0}
{
	owner_ = &owner;
	buildInputMap();
	addOptional
	(
		"hubOffset",
		"tipOffset",
		"vortexLawExponent"
	);
	parse(input);
	check();

	for (int i {0}; i < numberOfStations_; i++)
		airfoils_.push_back
		(
			std::make_unique<Airfoil>(input, *this)
		);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Blade::Iterator Blade::begin()
{
	return airfoils_.begin();
}


Blade::Constiterator Blade::begin() const
{
	return airfoils_.begin();
}


void Blade::build()						// TODO: airfoil optimization missing
{
	checkOffsets();

	buildAirfoils();

	// optimize airfoil geometries

	for (const auto& a : airfoils_)
		a->profile.wrap();

	buildSurfaces();
}


bool Blade::empty() const noexcept
{
	return airfoils_.empty();
}


Blade::Iterator Blade::end()
{
	return airfoils_.end();
}


Blade::Constiterator Blade::end() const
{
	return airfoils_.end();
}


const Airfoil* Blade::getAirfoilAt(const int station) const
{
	return &(*airfoils_.at(station));
}


int Blade::size() const noexcept
{
	return airfoils_.size();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
