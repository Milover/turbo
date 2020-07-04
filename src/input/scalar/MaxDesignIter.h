/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::MaxDesignIter

Description
	Class MaxDesignIter.

	Defaults to 100.

SourceFiles
	MaxDesignIter.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_MAX_DESIGN_ITER_H
#define INPUT_MAX_DESIGN_ITER_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class MaxDesignIter Declaration
\*---------------------------------------------------------------------------*/

class MaxDesignIter final
:
	public PositiveValue<std::size_t>
{
public:

	// Public static data

		inline static const String name {"MaxDesignIter"};


	// Constructors

		//- Default constructor
		MaxDesignIter() noexcept;

		//- Construct from a Integer,
		//  no aditional checking required
		explicit MaxDesignIter(const std::size_t i);


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
