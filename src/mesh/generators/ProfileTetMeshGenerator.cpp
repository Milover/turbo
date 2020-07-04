/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <algorithm>
#include <utility>
#include <limits>

#include "ProfileTetMeshGenerator.h"

#include "Bezier.h"
#include "BoundaryLayerField.h"
#include "BoxField.h"
#include "ComputeGeneral.h"
#include "Curve.h"
#include "Extrude.h"
#include "General.h"
#include "GmshGenerate.h"
#include "GmshRecombine.h"
#include "GmshTransfinite.h"
#include "Group.h"
#include "Line.h"
#include "PlanarSurface.h"
#include "Profile.h"
#include "Registry.h"
#include "Spline.h"
#include "Surface.h"
#include "Utility.h"
#include "Vector.h"
#include "Volume.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

Sptrvector<geometry::Curve> ProfileTetMeshGenerator::constructBoundary
(
	const design::Profile& profile
) const
{
	// make points
	Pointvector topBoundary {constructPoints(profile)};
	Pointvector botBoundary {topBoundary};

	// reverse bot boundary so the surface will be properly oriented
	std::reverse(botBoundary.begin(), botBoundary.end());

	// translate
	Vector translation {0.0, pitch_.value() * 0.5};

	for (auto& p : topBoundary)
		p += translation;

	for (auto& p : botBoundary)
		p -= translation;

	// make geometry
	Sptrvector<geometry::Curve> curves;

	curves.emplace_back
	(
		new geometry::Bezier {std::move(topBoundary)}
	);
	curves.emplace_back
	(
		new geometry::Bezier {std::move(botBoundary)}
	);
	curves.emplace			// outlet
	(
		curves.begin() + 1,
		new geometry::Line
		{
			curves[0]->endPtr(),
			curves[1]->startPtr()
		}
	);
	curves.emplace_back		// inlet
	(
		new geometry::Line
		{
			curves[2]->endPtr(),
			curves[0]->startPtr()
		}
	);

	return curves;
}


Sptrvector<geometry::Curve> ProfileTetMeshGenerator::constructContour
(
	const design::Profile& profile
) const
{
	// make points
	auto tmp {profile.points()};

	Pointvector topWall;
	Pointvector botWall;
	topWall.reserve(tmp.size());
	botWall.reserve(tmp.size());

	for (auto& [top, bot] : tmp)
	{
		topWall.emplace_back(top);
		botWall.emplace_back(bot);
	}

	// reverse bot wall so the surface will be properly oriented
	std::reverse(botWall.begin(), botWall.end());

	// make geometry
	Sptrvector<geometry::Curve> curves;

	curves.emplace_back
	(
		new geometry::Spline {std::move(botWall)}
	);
	curves.emplace_back
	(
		new geometry::Spline
		{
			curves[0]->endPtr(),
			std::move(topWall)
		}
	);
	curves.emplace_back		// trailing edge
	(
		new geometry::Line
		{
			curves[1]->endPtr(),
			curves[0]->startPtr()
		}
	);

	return curves;
}


ProfileTetMeshGenerator::Pointvector ProfileTetMeshGenerator::constructPoints
(
	const design::Profile& profile
) const noexcept
{
	Pointvector points;

	// (bezier) polygon end point at inlet/outlet
	auto plyEnd = [&](const Point& ltEdge, auto&& inwardNormal) -> Point
	{
		return ltEdge - inwardNormal * extension_.value() * chord_.value();
	};

	// mass emplace points
	auto massEmplace = [&](auto&&... ps) -> void
	{
		(points.emplace_back(std::forward<decltype(ps)>(ps)), ...);
	};
	massEmplace
	(
		plyEnd(profile.lePoint(), Vector::xAxis()),
		profile.lePoint(),
		profile.centroid(),
		profile.tePoint(),
		plyEnd(profile.tePoint(), -Vector::xAxis())
	);

	return points;
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ProfileTetMeshGenerator::ProfileTetMeshGenerator(const input::Registry& reg)
:
	BaseType {reg}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Uptr<ProfileTetMeshGenerator::Region> ProfileTetMeshGenerator::generate
(
	const input::Registry& reg,
	const design::Profile& profile
) const
{
	// make 1D
	auto boundary {constructBoundary(profile)};
	auto contour {constructContour(profile)};

	// make 2D
	Sptr<geometry::Surface> surface
	{
		new geometry::PlanarSurface {boundary, contour}
	};

	// set profile discretization
	interface::GmshTransfinite {}
	(
		interface::GmshTransfinite::Distribution::BUMP,
		discretization_.value(),
		reg.cref<input::ProfileBumpFactor>().value(),
		contour[0].get(),	// bot surface
		contour[1].get()	// top surface
	);
	interface::GmshTransfinite {}
	(
		static_cast<Integer>
		(
			static_cast<Float>(discretization_.value()) * teFactor_
		),
		contour[2].get()	// trailing edge
	);

	// construct mesh fields
	BoxField bgField {reg};
	bgField.setField();

	// set boundary layer field
	BoundaryLayerField blField {reg};
	blField.setEdges(contour);
	blField.setCorners
	(
		contour.back()->startPtr(),	// TE top
		contour.back()->endPtr()	// TE bot
	);
	blField.setField();

	if (!bgField.set() || !blField.set())
		return nullptr;

	// make 3D
	Sptr<geometry::Volume> volume
	{
		new geometry::Volume
		{
			geometry::operators::Extrude {}(surface, Vector::zAxis())
		}
	};

	// generate mesh
	interface::GmshGenerate {}();

	// define groups
	auto& surfaces {volume->boundaryRef()};

	Sptrvector<Patch> patches {};
	patches.reserve(8);		// we know the ordering and the ammount

	auto store = [&](auto& patchName, auto&&... surfs) -> void
	{
		patches.emplace_back
		(
			new Patch {patchName, std::forward<decltype(surfs)>(surfs)...}
		);
	};

	store("per_top",		surfaces[0]);
	store("outlet",			surfaces[1]);
	store("per_bot",		surfaces[2]);
	store("inlet",			surfaces[3]);
	store("profile_bot",	surfaces[4]);
	store("profile_top",	surfaces[5]);
	store("profile_te",		surfaces[6]);
	store("empty",			surfaces[7], surfaces[8]);

	Uptr<Region> region {new Region {"region", std::move(volume)}};
	region->storeSubgroups(std::move(patches));

	return region;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
