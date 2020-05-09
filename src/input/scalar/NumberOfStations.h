/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::NumberOfStations

Description
	Class NumberOfStations.

SourceFiles
	NumberOfStations.cpp

	Must be an odd integer, defaults to 1.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_NUMBER_OF_STATIONS_H
#define INPUT_NUMBER_OF_STATIONS_H

#include "Error.h"
#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class NumberOfStations Declaration
\*---------------------------------------------------------------------------*/

class NumberOfStations final
:
	public PositiveValue<Integer>
{
private:

	// Member functions

		//- Check input
		void check() const noexcept(ndebug) override;

	
public:

	// Public static data

		inline static const String name {"NumberOfStations"};


	// Constructors

		//- Default constructor
		NumberOfStations() noexcept;

		//- Construct from a Integer,
		explicit NumberOfStations(const Integer i);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
