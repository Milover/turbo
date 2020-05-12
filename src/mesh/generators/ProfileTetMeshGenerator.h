/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::ProfileTetMeshGenerator

Description
	ProfileTetMeshGenerator class.

SourceFiles
	ProfileTetMeshGenerator.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_PROFILE_HEX_MESH_GENERATOR_H
#define MESH_PROFILE_HEX_MESH_GENERATOR_H

#include <utility>

#include "Curve.h"
#include "Error.h"
#include "General.h"
#include "MeshGeneratorBase.h"
#include "Profile.h"
#include "Registry.h"
#include "Volume.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

/*---------------------------------------------------------------------------*\
					Class ProfileTetMeshGenerator Declaration
\*---------------------------------------------------------------------------*/

class ProfileTetMeshGenerator final
:
	public MeshGeneratorBase<design::Profile>
{
private:

	// Member functions

		// contour discretization / trailing edge discretization
		// NOTE: guesstimate
		inline static constexpr Float teFactor_ {0.02};


	// Member functions

		//- Construct the points used to create the boundary curves
		//	NOTE: seems to be stable for stagger angles up to about 85°
		[[nodiscard]] Pointvector constructPoints
		(
			const design::Profile& profile
		) const noexcept;

		//- Construct section boundary curves.
		[[nodiscard]] Sptrvector<geometry::Curve>
		constructBoundary(const design::Profile& profile) const;

		//- Construct profile contour curves
		[[nodiscard]] Sptrvector<geometry::Curve>
		constructContour(const design::Profile& profile) const;


public:

	// Public data

		inline static const String name {"ProfileTetMeshGenerator"};


	// Constructors

		//- Construct from data
		ProfileTetMeshGenerator(const input::Registry& reg);


	// Member functions

		//- Generate a structured 3D (H) hex mesh for an airfoil profile
		[[nodiscard]] Uptr<Region> generate
		(
			const input::Registry& reg,
			const design::Profile& profile
		) const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
