/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TotalPressureDifference

Description
	Class TotalPressureDifference.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TOTAL_PRESSURE_DIFFERENCE_H
#define INPUT_TOTAL_PRESSURE_DIFFERENCE_H

#include <type_traits>
#include <utility>

#include "BladeVelocity.h"
#include "Density.h"
#include "General.h"
#include "InitialDesign.h"
#include "InletVelocity.h"
#include "PositiveValue.h"
#include "OutletVelocity.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class TotalPressureDifference Definition
\*---------------------------------------------------------------------------*/

class TotalPressureDifference final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const Word name {"TotalPressureDifference"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Float, T>, int> = 0>
		>
		explicit TotalPressureDifference(T&& t)
		:
			PVBase {std::forward<T>(t)}
		{}

		//- Compute and construct
		TotalPressureDifference
		(
			const InletVelocity& c_1,
			const OutletVelocity& c_2,
			const BladeVelocity& U,
			const Density& rho
		)
		:
			TotalPressureDifference
			{
				compute::computeTotalPressureDifference
				(
					c_1.value(),
					c_2.value(),
					U.value(),
					rho.value()
				)
			}
		{}

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
