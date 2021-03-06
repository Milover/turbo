/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::MaxAbsBladeThicknessDistribution

Description
	Class MaxAbsBladeThicknessDistribution.

SourceFiles
	MaxAbsBladeThicknessDistribution.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_MAX_ABS_BLADE_THICKNESS_DISTRIBUTION_H
#define INPUT_MAX_ABS_BLADE_THICKNESS_DISTRIBUTION_H

#include <utility>

#include "Error.h"
#include "General.h"
#include "DistributedValue.h"
#include "MaxAbsBladeThickness.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
			Class MaxAbsBladeThicknessDistribution Declaration
\*---------------------------------------------------------------------------*/

class MaxAbsBladeThicknessDistribution final
:
	public DistributedValue<MaxAbsBladeThickness>
{
public:

	// Public static data

		inline static const String name {"MaxAbsBladeThicknessDistribution"};


	// Constructors

		//- Construct from a Polyline,
		//	no additional checking required
		template
		<
			typename T,
			typename = std::enable_if_t
			<
				std::is_same_v<typename RegBase::type, removeCVRef_t<T>>
			>
		>
		explicit MaxAbsBladeThicknessDistribution(T&& t);


	// Member functions

		//- Get object name
		String getName() const override;

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename T, typename>
MaxAbsBladeThicknessDistribution::MaxAbsBladeThicknessDistribution(T&& t)
:
	DVBase {std::forward<T>(t)}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
