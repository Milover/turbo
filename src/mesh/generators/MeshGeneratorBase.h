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

#include "General.h"
#include "Geometry.h"
#include "Variables.h"

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


	// Protected data

		input::Chord chord_;
		input::NumberOfCamberPoints discretization_;
		input::Pitch pitch_;


	// Constructors

		//- Construct from data
		MeshGeneratorBase
		(
			const input::Chord& chord,
			const input::NumberOfCamberPoints& discretization,
			const input::Pitch& pitch
		) noexcept;


	// Member functions

		//- Construct mesh boundary curves.
		//	Ordering should be: inlet, top, outlet, bot.
		//	Curve orientation should be in the streamwise direction
		//	from inlet to outlet. The inlet/outlet curve direction
		//	should be in the positive y direction (perpendicular
		//	to the streamwise direction)
		virtual Sptrvector<geometry::Curve>
		constructBoundary(const T&) const = 0;

		//- Construct section surface
		virtual Sptr<geometry::Surface> constructSection
		(
			const Sptrvector<geometry::Curve>& curves
		) const = 0;


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
		virtual Uptr<geometry::Volume> generate(const T& t) const = 0;

		//- Set chord
		void setChord(const input::Chord& chord) noexcept;

		//- Set pitch
		void setPitch(const input::Pitch& pitch) noexcept;

		//- Set pitch
		void setDiscretization
		(
			const input::NumberOfCamberPoints& discretization
		) noexcept;


	// Member operators

		//- Copy assignment operator
		MeshGeneratorBase& operator=(const MeshGeneratorBase&) = delete;

		//- Move assignment operator
		MeshGeneratorBase& operator=(MeshGeneratorBase&&) = default;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
