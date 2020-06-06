/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::MaxPassageWidth

Description
	Class MaxPassageWidth.

SourceFiles
	MaxPassageWidth.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_MAX_PASSAGE_WIDTH_H
#define INPUT_MAX_PASSAGE_WIDTH_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class MaxPassageWidth Declaration
\*---------------------------------------------------------------------------*/

class MaxPassageWidth final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"MaxPassageWidth"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit MaxPassageWidth(const Float f);


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
