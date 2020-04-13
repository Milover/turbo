/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::CamberPointSpacing

Description
	Class CamberPointSpacing.

SourceFiles
	CamberPointSpacing.cpp

	Defaults to COSINE.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_CAMBER_POINT_SPACING_H
#define INPUT_CAMBER_POINT_SPACING_H

#include "General.h"
#include "RegistryObject.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

namespace detail
{
	enum class SpacingType { LINEAR = 0, COSINE };
}

/*---------------------------------------------------------------------------*\
					Class CamberPointSpacing Declaration
\*---------------------------------------------------------------------------*/

class CamberPointSpacing final
:
	public RegistryObject<detail::SpacingType>
{
public:

	using Type = detail::SpacingType;


	// Public static data

		inline static const String name {"CamberPointSpacing"};


	// Constructors

		//- Default constructor
		CamberPointSpacing() noexcept;

		//- Construct from a String,
		//	take by value because it'll be formatted
		explicit CamberPointSpacing(String s);


	// Member functions

		//- Convert String keyword to Type,
		Type convert(String& s) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
