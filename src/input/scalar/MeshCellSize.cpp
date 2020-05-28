/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "MeshCellSize.h"

#include "Chord.h"
#include "General.h"
#include "RelMeshSize.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

MeshCellSize::MeshCellSize(const Float f)
:
	PVBase {f}
{}


MeshCellSize::MeshCellSize
(
	const Chord& c,
	const RelMeshSize& g

)
:
	MeshCellSize
	{
		c.value() * g.value()
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String MeshCellSize::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
