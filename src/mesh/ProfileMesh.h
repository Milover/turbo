/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::ProfileMesh

Description
	Abstract base class template for mesh classes.

SourceFiles
	ProfileMesh.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_PROFILE_MESH_H
#define MESH_PROFILE_MESH_H

#include <utility>

#include "Error.h"
#include "General.h"
#include "MeshBase.h"
#include "Profile.h"
#include "Registry.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

/*---------------------------------------------------------------------------*\
						Class ProfileMesh Declaration
\*---------------------------------------------------------------------------*/

class ProfileMesh final
:
	public MeshBase<design::Profile>
{
protected:

	// Member functions

		//- Check geometry
		void checkGeometry() const noexcept(ndebug) override;

		//- Create the mesh generator
		void createMeshGenerator() override;


public:

	// Constructors

		//- Default construct from geometry,
		//	creates an owned registry and creates a model
		ProfileMesh
		(
			const Sptr<design::Profile>& profile,
			const Path& file = Path {}
		);

		//- Construct from geometry with (owner) registry,
		//	creates a non-owned accessible registry and
		//	creates an owned model.
		ProfileMesh
		(
			const Sptr<design::Profile>& profile,
			const input::Registry& reg,
			const Path& file = Path {}
		);

		//- Construct from a profile with (owner) registry,
		//	creates a non-owned accessible registry and
		//	takes or shares ownership of a model
		template<typename T>
		ProfileMesh
		(
			const Sptr<design::Profile>& profile,
			const input::Registry& reg,
			T&& model,
			const Path& file = Path {}
		);

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename T>
ProfileMesh::ProfileMesh
(
	const Sptr<design::Profile>& profile,
	const input::Registry& reg,
	T&& model,
	const Path& file
)
:
	BaseType
	{
		profile,
		reg,
		std::forward<T>(model),
		file
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
