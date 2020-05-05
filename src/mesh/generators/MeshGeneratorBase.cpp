/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "MeshGeneratorBase.h"

#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

MeshGeneratorBase::MeshGeneratorBase
(
	const input::Chord& chord,
	const input::NumberOfCamberPoints& discretization,
	const input::Pitch& pitch
) noexcept
:
	chord_ {chord},
	discretization_ {discretization},
	pitch_ {pitch}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

MeshGeneratorBase::setChord(const input::Chord& chord) noexcept
{
	chord_ = chord;
}


MeshGeneratorBase::setDiscretization
(
	const input::NumberOfCamberPoints& discretization
) noexcept
{
	discretization_ = discretization;
}


MeshGeneratorBase::setPitch(const input::Pitch& pitch) noexcept
{
	pitch_ = pitch;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
