/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "SizeField.h"

#include "General.h"
#include "GmshSetFieldNumbers.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void SizeField::setValue
(
	const String& variable,
	const Floatvector& values
) const noexcept
{
	interface::GmshSetFieldNumbers {}(this, variable, values);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
