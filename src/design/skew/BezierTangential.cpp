/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>
#include <utility>

#include "BezierTangential.h"

#include "Error.h"
#include "General.h"
#include "InputRegistry.h"
#include "Profile.h"
#include "Registry.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void BezierTangential::construct
(
	const Float d_h,
	const Float d_s,
	const Float rho
) noexcept
{
	auto atZ = [](const Float z) -> Point
	{
		return Point {0.0, 0.0, z};
	};

	Point hub {atZ(r_h_.value())};
	Point tip {atZ(r_s_.value() - z_tip_.value())};
	Point mid {rho * (tip - hub)};

	tip.rotateX(d_s);
	mid.rotateX(d_h);

	mid += hub;

	bc_.reset
	(
		new math::BezierCurve<2>
		{
			std::move(hub),
			std::move(mid),
			std::move(tip)
		}
	);
}

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

BezierTangential::BezierTangential(const input::Registry& reg)
:
	r_h_ {reg.cref<input::HubRadius>()},
	r_s_ {reg.cref<input::ShroudRadius>()},
	z_tip_ {reg.cref<input::TipClearance>()}
{
	Float d_h {reg.cref<input::HubSkewAngle>().value()};
	Float d_s;
	if
	(
		input::InputRegistry::has(input::ShroudSkewAngle::name)
	)
		d_s = reg.cref<input::ShroudSkewAngle>().value();
	else
		d_s = d_h;

	construct
	(
		d_h,
		d_s,
		reg.cref<input::BezierSkewRelativeRadius>().value()
	);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void BezierTangential::skew(Profile& profile) const
{
	assert(!profile.wrapped());

	rRel input::RelRadius
	{
		input::Radius {profile.radius()},
		r_h_,
		r_s_,
		z_tip
	};

	profile.centerOn((*bc_)(rRel.value()));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
