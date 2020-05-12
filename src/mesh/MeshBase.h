/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::MeshBase

Description
	Abstract base class template for mesh classes.

SourceFiles
	MeshBase.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_MESH_BASE_H
#define MESH_MESH_BASE_H

#include <cassert>
#include <utility>

#include "Error.h"
#include "General.h"
#include "GmshWrite.h"
#include "Group.h"
#include "MeshGeneratorBase.h"
#include "Registry.h"
#include "Surface.h"
#include "TurboBase.h"
#include "Volume.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

/*---------------------------------------------------------------------------*\
						Class MeshBase Definition
\*---------------------------------------------------------------------------*/

template<typename Geometry>
class MeshBase
:
	public TurboBase
{
protected:

	using Region = Group<geometry::Volume>;
	using BaseType = MeshBase<Geometry>;


	// Protected data

		Uptr<Region> mesh_ {nullptr};
		Uptr<MeshGeneratorBase<Geometry>> mGen_ {nullptr};


	// Member functions

		//- Check if geometry is valid
		virtual void checkGeometry(const Geometry& geometry) const = 0;

		//- Create the mesh generator
		virtual void createMeshGenerator() = 0;


	// Constructors

		//- Default constructor
		//	creates an owned registry and creates a model
		MeshBase(const Path& file = Path {});

		//- Construct with (owner) registry,
		//	creates a non-owned accessible registry and
		//	creates an owned model.
		MeshBase
		(
			const input::Registry& reg,
			const Path& file = Path {}
		);

		//- Construct with (owner) registry,
		//	creates a non-owned accessible registry and
		//	takes or shares ownership of a model
		template<typename U>
		MeshBase
		(
			const input::Registry& reg,
			U&& model,
			const Path& file = Path {}
		);


public:

	// Constructors

		//- Copy constructor
		MeshBase(const MeshBase&) = delete;

		//- Move constructor
		MeshBase(MeshBase&&) = delete;


	//- Destructor
	virtual ~MeshBase() = default;


	// Member functions

		//- Generate a mesh
		//	NOTE: activates the (local) model
		//	XXX: no error handling/quality checks
		void build(const Geometry& geometry);

		//- Check if empty
		[[nodiscard]] bool empty() const noexcept;

		//- Get the region cref
		[[nodiscard]] const Uptr<Region>& meshCRef() const noexcept;

		//- Get the region ref
		[[nodiscard]] Uptr<Region>& meshRef() noexcept;

		//- Clear mesh and reset the mesh generator
		//	NOTE: activates the (local) model
		void reset();

		//- Write the mesh in .msh format
		//	NOTE: activates the (local) model
		void write() const override;


	// Member operators

		//- Disallow copy assignment
		MeshBase& operator=(const MeshBase&) = delete;

		//- Disallow move assignment
		MeshBase& operator=(MeshBase&&) = delete;

};


// * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * * //

template<typename Geometry>
MeshBase<Geometry>::MeshBase
(
	const Path& file
)
:
	TurboBase {file}
{
	this->setFile("mesh", ".msh");
}


template<typename Geometry>
MeshBase<Geometry>::MeshBase
(
	const input::Registry& reg,
	const Path& file
)
:
	TurboBase {reg, file}
{
	this->setFile("mesh", ".msh");
}


template<typename Geometry>
template<typename U>
MeshBase<Geometry>::MeshBase
(
	const input::Registry& reg,
	U&& model,
	const Path& file
)
:
	TurboBase
	{
		reg,
		std::forward<U>(model),
		file
	}
{
	this->setFile("mesh", ".msh");
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename Geometry>
void MeshBase<Geometry>::build(const Geometry& geometry)
{
	this->reset();

	this->checkGeometry(geometry);
	this->createMeshGenerator();

	this->mesh_ = this->mGen_->generate(*this->data_, geometry);

	// check mesh
	// handle errors
}


template<typename Geometry>
bool MeshBase<Geometry>::empty() const noexcept
{
	return static_cast<bool>(this->mesh_);
}


template<typename Geometry>
const Uptr<typename MeshBase<Geometry>::Region>&
MeshBase<Geometry>::meshCRef() const noexcept
{
	return this->mesh_;
}


template<typename Geometry>
Uptr<typename MeshBase<Geometry>::Region>&
MeshBase<Geometry>::meshRef() noexcept
{
	return this->mesh_;
}


template<typename Geometry>
void MeshBase<Geometry>::write() const
{
	assert(this->mesh_);

	this->model_->activate();

	interface::GmshWrite {}(this->file_);
}


template<typename Geometry>
void MeshBase<Geometry>::reset()
{
	this->model_->activate();

	this->mesh_.reset(nullptr);
	this->mGen_.reset(nullptr);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
