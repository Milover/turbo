/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::MeshGeneratorBase

Description
	Abstract base class template for mesh generator classes

SourceFiles
	MeshGeneratorBase.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_MESH_GENERATOR_BASE_H
#define MESH_MESH_GENERATOR_BASE_H

#include <vector>

#include "General.h"
#include "Group.h"
#include "Registry.h"
#include "Surface.h"
#include "Variables.h"
#include "Vector.h"
#include "Volume.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

/*---------------------------------------------------------------------------*\
					Class MeshGeneratorBase Declaration
\*---------------------------------------------------------------------------*/

template<typename T>
class MeshGeneratorBase
{
protected:

	using Point = Vector;
	using Pointvector = std::vector<Point>;
	using Patch = Group<geometry::Surface>;
	using Region = Group<geometry::Volume>;
	using BaseType = MeshGeneratorBase<T>;


	// Protected data

		input::Chord chord_;
		input::NumberOfCamberPoints discretization_;
		input::Pitch pitch_;
		input::SectionExtensionFactor extension_;


	// Constructors

		//- Construct from data
		MeshGeneratorBase(const input::Registry& reg);


public:

	// Constructors

		//- Copy constructor
		MeshGeneratorBase(const MeshGeneratorBase&) = delete;

		//- Move constructor
		MeshGeneratorBase(MeshGeneratorBase&&) = default;


	//- Destructor
	virtual ~MeshGeneratorBase() = default;


	// Member functions

		//- Generate the mesh
		virtual Uptr<Region> generate
		(
			const input::Registry& reg,
			const T&
		) const = 0;


	// Member operators

		//- Copy assignment operator
		MeshGeneratorBase& operator=(const MeshGeneratorBase&) = delete;

		//- Move assignment operator
		MeshGeneratorBase& operator=(MeshGeneratorBase&&) = default;

};


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

template<typename T>
MeshGeneratorBase<T>::MeshGeneratorBase(const input::Registry& reg)
:
	chord_
	{
		reg.cref<input::Chord>()
	},
	discretization_
	{
		reg.cref<input::NumberOfCamberPoints>()
	},
	pitch_
	{
		reg.cref<input::Pitch>()
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
