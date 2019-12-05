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

#include "Airfoil.h"
#include "Blade.h"
#include "ComponentBase.h"
#include "Error.h"
#include "InputObjectBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Blade::checkNumberOfStations() const
{
	if (numberOfStations_ == 0)
		THROW_RUNTIME_ERROR("number of stations == 0");
}


void Blade::checkOffsets() const
{
	double offsets
	{
		get("hubOffset") + get("tipOffset")
	};

	if
	(
		isLessOrEqual(get("span"), offsets)
	)
		THROW_RUNTIME_ERROR("offsets larger than span");
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

Blade::iterator Blade::begin()
{
	return airfoils_.begin();
}


Blade::const_iterator Blade::begin() const
{
	return airfoils_.begin();
}


void Blade::build()
{
	checkOffsets();

	for (const auto& a : airfoils_)
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


bool Blade::empty() const noexcept
{
	return airfoils_.empty();
}


Blade::iterator Blade::end()
{
	return airfoils_.end();
}


Blade::const_iterator Blade::end() const
{
	return airfoils_.end();
}


const Airfoil* Blade::getAirfoilAt(const int station) const
{
	return &(*airfoils_.at(station));
}


Vectorpair<int> Blade::getDimTags() const noexcept
{
	Vectorpair<int> dimTags;
	Vectorpair<int> temp;

	for (const auto& a : airfoils_)
	{
		temp = a->getDimTags();

		for (const auto& p : temp)
			dimTags.push_back(p);
	}

	return std::move(dimTags);
}


int Blade::size() const noexcept
{
	return airfoils_.size();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
