/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "SmootherIter.h"

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

SmootherIter::SmootherIter() noexcept
:
	PVBase {10}
{}


SmootherIter::SmootherIter(const Integer i)
:
	PVBase {i}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String SmootherIter::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
