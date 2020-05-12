/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::YPlus

Description
	Class YPlus.

	Defaults to 150.

SourceFiles
	YPlus.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_YPLUS_H
#define INPUT_YPLUS_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class YPlus Declaration
\*---------------------------------------------------------------------------*/

class YPlus final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"YPlus"};


	// Constructors

		//- Default constructor
		YPlus() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit YPlus(const Float f);


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
