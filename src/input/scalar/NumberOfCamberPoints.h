/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::NumberOfCamberPoints

Description
	Class NumberOfCamberPoints.

SourceFiles
	NumberOfCamberPoints.cpp

	Defaults to 250.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_NUMBER_OF_CAMBER_POINTS_H
#define INPUT_NUMBER_OF_CAMBER_POINTS_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class NumberOfCamberPoints Declaration
\*---------------------------------------------------------------------------*/

class NumberOfCamberPoints final
:
	public PositiveValue<Integer>
{
public:

	// Public static data

		inline static const String name {"NumberOfCamberPoints"};


	// Constructors

		//- Default constructor
		NumberOfCamberPoints() noexcept;

		//- Construct from a Integer,
		//  no aditional checking required
		explicit NumberOfCamberPoints(const Integer i);


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
