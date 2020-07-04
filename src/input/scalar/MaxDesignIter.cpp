/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "MaxDesignIter.h"

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

MaxDesignIter::MaxDesignIter() noexcept
:
	PVBase {100ul}
{}


MaxDesignIter::MaxDesignIter(const std::size_t i)
:
	PVBase {i}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String MaxDesignIter::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
