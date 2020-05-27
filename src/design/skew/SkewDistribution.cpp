/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "SkewDistribution.h"

#include "BezierTangential.h"
#include "Error.h"
#include "General.h"
#include "InputRegistry.h"
#include "NoSkew.h"
#include "Profile.h"
#include "Registry.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void SkewDistribution::createSkewDistribution(const input::Registry& reg)
{
	if
	(
		!input::InputRegistry::has("SkewDistribution")
	)
		distr_.reset(new NoSkew {});
	else
	{
		auto type
		{
			input::InputRegistry::get("SkewDistribution")
		};

		if (type == NoSkew::name)
			distr_.reset
			(
				new NoSkew {}
			);
		else if (type == BezierTangential::name)
			distr_.reset
			(
				new BezierTangential {reg}
			);
		else
			error(FUNC_INFO, "unknown SkewDistribution: ", type);
	}
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

SkewDistribution::SkewDistribution(const input::Registry& reg)
{
	reset(reg);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void SkewDistribution::skew(Profile& profile) const
{
	distr_->skew(profile);
}


void SkewDistribution::reset(const input::Registry& reg)
{
	createSkewDistribution(reg);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
