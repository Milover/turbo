/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "ShroudRadius.h"

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ShroudRadius::ShroudRadius(const Float f)
:
	PVBase {f}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String ShroudRadius::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
