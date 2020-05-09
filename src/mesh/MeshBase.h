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
#include "MeshGeneratorBase.h"
#include "Registry.h"
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

template<typename T>
class MeshBase
:
	public TurboBase
{
protected:

	using BaseType = MeshBase<T>;


	// Protected data

		const Sptr<T> geometry_;
		Uptr<geometry::Volume> mesh_ {nullptr};
		Uptr<MeshGeneratorBase<T>> mGen_ {nullptr};


	// Member functions

		//- Check if geometry is valid
		virtual void checkGeometry() const = 0;

		//- Create the mesh generator
		virtual void createMeshGenerator() = 0;


	// Constructors

		//- Default construct from geometry,
		//	creates an owned registry and creates a model
		MeshBase
		(
			const Sptr<T>& geometry,
			const Path& file = Path {}
		);

		//- Construct from geometry with (owner) registry,
		//	creates a non-owned accessible registry and
		//	creates an owned model.
		MeshBase
		(
			const Sptr<T>& geometry,
			const input::Registry& reg,
			const Path& file = Path {}
		);

		//- Construct from a profile with (owner) registry,
		//	creates a non-owned accessible registry and
		//	takes or shares ownership of a model
		template<typename U>
		MeshBase
		(
			const Sptr<T>& geometry,
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
		void build() override;

		//- Check if empty
		[[nodiscard]] bool empty() const noexcept;

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

template<typename T>
MeshBase<T>::MeshBase
(
	const Sptr<T>& geometry,
	const Path& file
)
:
	TurboBase {file},
	geometry_ {geometry}
{
	adjustFilename("mesh", ".msh");
}


template<typename T>
MeshBase<T>::MeshBase
(
	const Sptr<T>& geometry,
	const input::Registry& reg,
	const Path& file
)
:
	TurboBase {reg, file},
	geometry_ {geometry}
{
	adjustFilename("mesh", ".msh");
}


template<typename T>
template<typename U>
MeshBase<T>::MeshBase
(
	const Sptr<T>& geometry,
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
	},
	geometry_ {geometry}
{
	adjustFilename("mesh", ".msh");
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T>
void MeshBase<T>::build()
{
	this->checkGeometry();

	this->reset();

	this->mesh_ = this->mGen_->generate
	(
		*this->data_,
		*this->geometry_
	);

	// check mesh
	// handle errors
}


template<typename T>
bool MeshBase<T>::empty() const noexcept
{
	return static_cast<bool>(this->mesh_);
}


template<typename T>
void MeshBase<T>::write() const
{
	assert(this->mesh_);

	this->model_->activate();

	interface::GmshWrite {}(this->file_);
}


template<typename T>
void MeshBase<T>::reset()
{
	this->model_->activate();
	this->mesh_.reset(nullptr);

	this->createMeshGenerator();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
