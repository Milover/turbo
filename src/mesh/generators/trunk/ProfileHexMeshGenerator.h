/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::ProfileHexMeshGenerator

Description
	ProfileHexMeshGenerator class.

	BUG:
		Crash at constructBoundary()::massTransfinite(); Eats a curve
		that doesn't seem to exist, haven't fixed because this approach
		doesn't seem promissing.
	
	NOTE:
		Left some notes in the source file.

		At a glance the current approach doesn't seem to be a good one:
			1 - We have to segment the geometry into about 10 curves minimum,
				which raises issues about how certain parts should be
				discretized. If we want to avoid using the 'Bump' distribution
				we're left with about 14 curves.
			2 - Even if we manage to deal with the issue of highly segmented
				geometry for moderately high stagger the resulting geometry
				can be fairly poor if valid at all.
			3 - Haven't tried to mesh at all, although judging by the geometry
				we're probably not missing much.

		Moving to hybrid tet meshing for now, maybe we come back to this at
		some point.

SourceFiles
	ProfileHexMeshGenerator.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_PROFILE_HEX_MESH_GENERATOR_H
#define MESH_PROFILE_HEX_MESH_GENERATOR_H

#include <utility>

#include "Error.h"
#include "General.h"
#include "Geometry.h"
#include "MeshGeneratorBase.h"
#include "Registry.h"
#include "Profile.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

/*---------------------------------------------------------------------------*\
					Class ProfileHexMeshGenerator Declaration
\*---------------------------------------------------------------------------*/

class ProfileHexMeshGenerator final
:
	public MeshGeneratorBase<design::Profile>
{
private:

	// Private data

		input::SmootherIter smootherIter_;

		// XXX: should this be user input?
		inline static constexpr Float progFactor_ {1.2};
		inline static constexpr Float bumpFactor_ {0.1};


	// Member functions

		//- Construct mesh boundary curves.
		//	Ordering is: inlet, top, bot, outlet.
		//	The blade contour is oriented in the positive x direction.
		//	The inlet/outlet (bezier) segments are oriented away from the blade.
		//	The Inlet/outlet curve (line) direction is in positive y direction.
		Sptrvector<geometry::Curve>
		constructBoundary(const design::Profile& profile) const;

		//- Construct section surface
		Sptr<geometry::Surface> constructSection
		(
			Sptrvector<geometry::Curve>&& curves
		) const;

		//- Compute inlet/outlet segment (bezier curve) nodes.
		//	The inlet/outlet is placed 1 chord length from the LE/TE point.
		//	NOTE: oriented from LE/TE point outwards
		Pointvector inletOutletSegment
		(
			const Point& point,
			const Vector& camberDirection,
			const Vector& inwardNormal
		) const noexcept;


public:

	// Public data

		inline static const String name {"ProfileHexMeshGenerator"};


	// Constructors

		//- Construct from data
		ProfileHexMeshGenerator(const input::Registry& reg);


	// Member functions

		//- Generate a structured 3D (H) hex mesh for an airfoil profile
		Uptr<geometry::Volume> generate
		(
			const design::Profile& profile
		) const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
