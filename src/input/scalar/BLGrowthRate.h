/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::BLGrowthRate

Description
	Class BLGrowthRate.

	Defaults to 1.2.

SourceFiles
	BLGrowthRate.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_BL_GROWTH_RATE_H
#define INPUT_BL_GROWTH_RATE_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class BLGrowthRate Declaration
\*---------------------------------------------------------------------------*/

class BLGrowthRate final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"BLGrowthRate"};


	// Constructors

		//- Default constructor
		BLGrowthRate() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit BLGrowthRate(const Float f);


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
