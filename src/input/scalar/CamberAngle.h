/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::CamberAngle

Description
	Class CamberAngle.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_CAMBER_ANGLE_H
#define INPUT_CAMBER_ANGLE_H

#include <type_traits>
#include <utility>

#include "General.h"
#include "RegistryObject.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class CamberAngle Definition
\*---------------------------------------------------------------------------*/

class CamberAngle final
:
	public RegistryObject<Float>
{
public:

	// Public static data

		inline static const Word name {"CamberAngle"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Float, T>, int> = 0>
		>
		explicit CamberAngle(T&& t)
		:
			RegBase {std::forward<T>(t)}
		{}

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
