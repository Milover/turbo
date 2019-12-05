/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include "Blade.h"
#include "BladeRow.h"
#include "ComponentBase.h"
#include "InputObjectBase.h"
#include "Error.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void BladeRow::checkHubTipRatio() const
{
	if
	(
		!isInRange(get("hubShroudRatio"), 0.0, 1.0)
	)
		THROW_RUNTIME_ERROR("value of keyword 'hubShroudRatio' out of range [0, 1]");
}


double BladeRow::computeArea() const
{
	double hubRadius {computeHubRadius()};

	return pi *
	(
		std::pow(get("shroudRadius"), 2) - std::pow(hubRadius, 2)
	);
}


double BladeRow::computeAxialVelocity() const
{
	double area {computeArea()};

	return get("volumeFlowRate") / (3600.0 * area);
}


double BladeRow::computeHubRadius() const
{
	return get("shroudRadius") * get("hubShroudRatio");
}


double BladeRow::computeSpan() const
{
	double hubRadius {computeHubRadius()};
	double span
	{
		get("shroudRadius") - hubRadius - get("tipGap")
	};

	if
	(
		isLessOrEqual(span, 0.0)
	)
		THROW_RUNTIME_ERROR("tip gap too large");

	return span;
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void BladeRow::buildInputMap() noexcept
{
	store("hubShroudRatio",	0.5);	// [-]
	store("numberOfBlades",	NAN);	// [-]
	store("shroudRadius",	NAN);	// [m]
	store("tipGap",			0.001);	// [m]
}


void BladeRow::check() const
{
	for (const auto& [key, value] : this->inputMap_)
		if (isLessOrEqual(value, 0.0))
			THROW_RUNTIME_ERROR("value of keyword '" + key + "' <= 0");
	
	checkHubTipRatio();
}


void BladeRow::computeAndStore()
{
	store
	(
		"area",				// [m2]
		computeArea()
	);
	store
	(
		"axialVelocity",	// [m s-1]
		computeAxialVelocity()
	);
	store
	(
		"hubRadius",		// [m]
		computeHubRadius()
	);
	store
	(
		"span",				// [m]
		computeSpan()
	);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

BladeRow::BladeRow
(
	const Stringmap<>& input,
	const ComponentBase& owner
)
{
	owner_ = &owner;
	buildInputMap();
	addOptional
	(
		"hubShroudRatio",
		"tipGap"
	);
	parse(input);
	check();

	blade_.reset
	(
		new Blade {input, *this}
	);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void BladeRow::build()
{
	computeAndStore();

	blade_->build();
}


Vectorpair<int> BladeRow::getDimTags() const noexcept
{
	return std::move(blade_->getDimTags());
}


const Blade* BladeRow::getBlade() const noexcept
{
	return &(*blade_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
