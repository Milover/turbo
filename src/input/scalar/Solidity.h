/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::Solidity

Description
	Class Solidity.

	Defaults to 1.0.

SourceFiles
	Solidity.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_SOLIDITY_H
#define INPUT_SOLIDITY_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class Solidity Declaration
\*---------------------------------------------------------------------------*/

class Solidity final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"Solidity"};


	// Constructors

		//- Default constructor
		Solidity() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit Solidity(const Float f);


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
