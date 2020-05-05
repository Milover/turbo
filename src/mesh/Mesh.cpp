/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "Mesh.h"

#include "Error.h"
#include "GmshWrite.h"
#include "InputRegistry.h"
#include "TurboBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Mesh::Mesh
(
	const input::Registry& reg
	geometry::Model&& mod
)
:
	TurboBase {reg, std::move(mod)}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Mesh::build(const design::Profile& profile)
{
	if (profile.empty())
		error(FUNC_INFO, "profile not built");
	else if (profile.wrapped())
		error(FUNC_INFO, "profile is wrapped");

	clear();

	MeshGenerator generator {*data_};

	mesh_ = std::move
	(
		generator.generate(profile)
	);

	// check
	// handle errors
}


void Mesh::clear() noexcept
{
	model_->activate();

	mesh_.reset(nullptr);
}


void Mesh::write() const noexcept(ndebug)
{
	if (!mesh_)
		error(FUNC_INFO, "mesh not built");

	model_->activate();

	interface::GmshWrite(model_.name() + ".msh");
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
