/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::ProfileHexMeshGenerator

Description
	ProfileHexMeshGenerator class.

SourceFiles
	ProfileHexMeshGenerator.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_PROFILE_HEX_MESH_GENERATOR_H
#define MESH_PROFILE_HEX_MESH_GENERATOR_H

#include <utility>
#include <vector>

#include "Error.h"
#include "General.h"
#include "Geometry.h"
#include "MeshGeneratorBase.h"
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
	MeshGeneratorBase<design::Profile>
{
private:

	// Private data

		input::SmootherIter smootherIter_;

		// XXX: should this be user input?
		inline static constexpr Float progFactor_ {1.2};
		inline static constexpr Float bumpFactor_ {0.1};


	// Member functions

		//- Compute inlet/outlet segment (bezier curve) nodes.
		//	The inlet/outlet is placed 1 chord length from the LE/TE point.
		//	NOTE: oriented from LE/TE point outwards
		std::vector<Point> inletOutletSegment
		(
			const Point& point,
			const Vector& camberDirection,
			const Vector& inwardNormal
		) const noexcept


protected:

	// Member functions

		//- Construct mesh boundary curves.
		//	Ordering is: inlet, top, bot, outlet.
		//	The blade contour is oriented in the positive x direction.
		//	The inlet/outlet (bezier) segments are oriented away from the blade.
		//	The Inlet/outlet curve (line) direction is in positive y direction.
		Sptrvector<geometry::Curve>
		constructBoundary(const design::Profile& profile) const override;

		//- Construct section surface
		Sptr<geometry::Surface> constructSection
		(
			const Sptrvector<geometry::Curve>& curves
		) const override;


public:

	// Constructors

		//- Construct from data
		ProfileHexMeshGenerator
		(
			const input::Chord& chord,
			const input::NumberOfCamber& discretization,
			const input::Pitch& pitch
		);


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
