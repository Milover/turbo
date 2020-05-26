/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "ProfileMesh.h"

#include "Error.h"
#include "InputRegistry.h"
#include "Profile.h"
#include "ProfileTetMeshGenerator.h"
#include "Registry.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void ProfileMesh::checkGeometry
(
	const design::Profile& profile
) const noexcept(ndebug)
{
	if (profile.empty())
		error(FUNC_INFO, "profile not built");
	else if (profile.wrapped())
		error(FUNC_INFO, "profile is wrapped");
}


void ProfileMesh::createMeshGenerator()
{
	if
	(
		!input::InputRegistry::has("ProfileMeshGenerator")
	)
		mGen_.reset
		(
			new ProfileTetMeshGenerator {*data_}
		);
	else
	{
		auto type
		{
			input::InputRegistry::get("ProfileMeshGenerator")
		};

		if (type == ProfileTetMeshGenerator::name)
			mGen_.reset
			(
				new ProfileTetMeshGenerator {*data_}
			);
		else
			error(FUNC_INFO, "unknown ProfileMeshGenerator: ", type);
	}
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ProfileMesh::ProfileMesh(const Path& parentCwd)
:
	BaseType {parentCwd}
{}


ProfileMesh::ProfileMesh
(
	const input::Registry& reg,
	const Path& parentCwd
)
:
	BaseType {reg, parentCwd}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
