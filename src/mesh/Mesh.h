/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::Mesh

Description
	Mesh class

SourceFiles
	Mesh.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_MESH_H
#define MESH_MESH_H

#include <type_traits>

#include "Error.h"
#include "General.h"
#include "Geometry.h"
#include "MeshGenerators.h"
#include "Profile.h"
#include "TurboBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

/*---------------------------------------------------------------------------*\
						Class Mesh Declaration
\*---------------------------------------------------------------------------*/

class Mesh
:
	public TurboBase
{
protected:

	// Protected data

		Uptr<geometry::Volume> mesh_ {nullptr};


public:

	// Constructors

		//- Default constructor
		Mesh() = default;

		//- Construct from a registry and a model
		Mesh
		(
			const input::Registry& reg,
			geometry::Model&& mod
		);

		//- Copy constructor
		Mesh(const Mesh&) = delete;

		//- Move constructor
		Mesh(Mesh&&) = delete;


	//- Destructor
	~Mesh() = default;


	// Member functions

		//- Generate a mesh
		//	NOTE: activates the (local) model
		void build(const design::Profile& profile);

		//- Clear the mesh and the geometry
		//	NOTE: activates the (local) model
		void clear() noexcept;

		//- Write the mesh in .msh format
		//	NOTE: activates the (local) model
		void write() const noexcept(ndebug);


	// Member operators

		//- Disallow copy assignment
		Mesh& operator=(const Mesh&) = delete;

		//- Disallow move assignment
		Mesh& operator=(Mesh&&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
