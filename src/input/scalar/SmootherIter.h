/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::SmootherIter

Description
	Class SmootherIter.

SourceFiles
	SmootherIter.cpp

	Defaults to 10.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_SMOOTHER_ITER_H
#define INPUT_SMOOTHER_ITER_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class SmootherIter Declaration
\*---------------------------------------------------------------------------*/

class SmootherIter final
:
	public PositiveValue<Integer>
{
public:

	// Public static data

		inline static const String name {"SmootherIter"};


	// Constructors

		//- Default constructor
		SmootherIter() noexcept;

		//- Construct from a Integer,
		//  no aditional checking required
		explicit SmootherIter(const Integer i);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
