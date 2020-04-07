/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::IncidenceAngle

Description
	Class IncidenceAngle.

	Defaults to 0.0.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_INCIDENCE_ANGLE_H
#define INPUT_INCIDENCE_ANGLE_H

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
						Class IncidenceAngle Definition
\*---------------------------------------------------------------------------*/

class IncidenceAngle final
:
	public RegistryObject<Float>
{
public:

	// Public static data

		inline static const Word name {"IncidenceAngle"};


	// Constructors

		//- Default constructor
		IncidenceAngle() noexcept
		:
			RegBase {0.0}
		{}

		//- Construct from a Float,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Float, T>, int> = 0>
		>
		explicit IncidenceAngle(T&& t)
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
