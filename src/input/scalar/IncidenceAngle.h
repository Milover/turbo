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

SourceFiles
	IncidenceAngle.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_INCIDENCE_ANGLE_H
#define INPUT_INCIDENCE_ANGLE_H

#include "General.h"
#include "RegistryObject.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class IncidenceAngle Declaration
\*---------------------------------------------------------------------------*/

class IncidenceAngle final
:
	public RegistryObject<Float>
{
public:

	// Public static data

		inline static const String name {"IncidenceAngle"};


	// Constructors

		//- Default constructor
		IncidenceAngle() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit IncidenceAngle(const Float f);


	// Member functions

		//- Get object name
		String getName() const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
