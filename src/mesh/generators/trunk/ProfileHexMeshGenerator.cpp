/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <utility>

#include "ProfileHexMeshGenerator.h"

#include <gmsh.h>

#include "General.h"
#include "Geometry.h"
#include "GeometryInterface.h"
#include "Profile.h"
#include "Registry.h"
#include "Utility.h"
#include "Variables.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

Sptrvector<geometry::Curve> ProfileHexMeshGenerator::constructBoundary
(
	const design::Profile& profile
) const
{
	// mass translate points
	auto massTranslate = []
	(
		const Vector& v,
		auto&&... points
	) -> void
	{
		auto translate = [&] (auto& pts) -> void
		{
			for (auto& p : pts)
				p += v;
		};
		
		(translate(points), ...);
	};

	// mass designate as transfinite
	auto massTransfinite = [&]
	(
		const auto distribution,
		const Float factor,
		auto&&... curves
	) -> void
	{
		geometry::interface::GmshTransfinite gt {};

		(
			gt
			(
				std::forward<decltype(curves)>(curves),
				distribution,
				discretization_.value(),
				factor
			),
			...
		);
	};

	// mass store curves
	auto massStore = [](auto& bndry, auto&&... curves) -> void
	{
		bndry.reserve(sizeof...(curves));
		(
			bndry.emplace_back
			(
				new removeCVRef_t<decltype(curves)>
				{
					std::forward<decltype(curves)>(curves)
				}
			),
			...
		);
	};

	// create
	auto tmp {profile.points()};

	Pointvector bladeTop;
	Pointvector bladeBot;
	bladeTop.reserve(tmp.size());
	bladeBot.reserve(tmp.size());

	for (auto&& [top, bot] : tmp)
	{
		bladeTop.emplace_back(top);
		bladeBot.emplace_back(bot);
	}

	Pointvector inPerTop
	{
		inletOutletSegment
		(
			profile.lePoint(),
			profile.leDirection(),
			Vector::xAxis()
		)
	};
	Pointvector outPerTop
	{
		inletOutletSegment
		(
			profile.tePoint(),
			profile.teDirection(),
			-Vector::xAxis()
		)
	};

	// copy
	Pointvector inPerBot {inPerTop};
	Pointvector outPerBot {outPerTop};

	// because the points are currently on the midline of the section
	Vector translation {0.0, pitch_.value() / 2.0};

	// translate
	massTranslate
	(
		-translation,
		bladeTop,
		inPerTop,
		outPerTop
	);
	massTranslate
	(
		translation,
		bladeBot,
		inPerBot,
		outPerBot
	);

	// construct
	geometry::Bezier inPerTop_g
	{
		std::move(inPerTop)
	};
	geometry::Bezier outPerTop_g
	{
		std::move(outPerTop)
	};
	geometry::Bezier inPerBot_g
	{
		std::move(inPerBot)
	};
	geometry::Bezier outPerBot_g
	{
		std::move(outPerBot)
	};

	// FIXME:
	// 	There is a gap at the trailing edge which needs to be closed with
	// 	2 lines (top and bot parts). There is also the issue of how to
	// 	discretize these two guys.
/*
	geometry::Line teTop_g
	{
	};
	geometry::Line teBot_g
	{
	};
*/

	geometry::Spline bladeTop_g
	{
	//	inPerTop_g.startPtr(),
	//	std::move(bladeTop),
	//	outPerTop_g.startPtr()
		std::move(bladeTop)
	};
	geometry::Spline bladeBot_g
	{
	//	inPerBot_g.startPtr(),
	//	std::move(bladeBot),
	//	outPerBot_g.startPtr()
		std::move(bladeBot)
	};

	geometry::Line inlet_g
	{
		inPerTop_g.endPtr(),
		inPerBot_g.endPtr()
	};
	geometry::Line outlet_g
	{
		outPerTop_g.endPtr(),
		outPerBot_g.endPtr()
	};

gmsh::model::occ::synchronize();
gmsh::graphics::draw();
gmsh::fltk::run();
debug::echo("constructed curves");

	// BUG: crashes here, haven't checked why
	// make transfinite
	massTransfinite
	(
		geometry::interface::GmshTransfinite::Distribution::PROGRESSION,
		progFactor_,
		&inPerTop_g,
		&outPerTop_g,
		&inPerBot_g,
		&outPerTop_g
	);
	massTransfinite
	(
		geometry::interface::GmshTransfinite::Distribution::BUMP,
		bumpFactor_,
		&bladeTop_g,
		&bladeBot_g,
		&inlet_g,
		&outlet_g
	);

debug::echo("set transfinite");
	// set names
	// FIXME: physical groups not implemented

	// store
	Sptrvector<geometry::Curve> boundary;
	
	massStore
	(
		boundary,
		std::move(inlet_g),
		std::move(inPerTop_g),
		std::move(bladeTop_g),
		std::move(outPerTop_g),
		std::move(outlet_g),
		std::move(outPerBot_g),
		std::move(bladeBot_g),
		std::move(inPerBot_g)
	);
debug::echo("stored");

	return boundary;
}


Sptr<geometry::Surface> ProfileHexMeshGenerator::constructSection
(
	Sptrvector<geometry::Curve>&& curves
) const
{
	Sptr<geometry::Surface> surface
	{
		new geometry::PlanarSurface {std::move(curves)}
	};

	auto& boundary {surface->boundaryCRef()};

	surface->storeCorners
	(
		boundary[0]->startPtr(),		// inlet start point
		boundary[0]->endPtr(),			// inlet end point
		boundary[4]->endPtr(),			// outlet end point
		boundary[4]->startPtr()			// outlet start point
	);

	// set names
	// FIXME: physical groups not implemented

	geometry::interface::GmshTransfinite {}(surface.get());
	geometry::interface::GmshRecombine {}(surface.get());
	geometry::interface::GmshSmooth {}
	(
		surface.get(),
		smootherIter_.value()
	);

	return surface;
}


ProfileHexMeshGenerator::Pointvector ProfileHexMeshGenerator::inletOutletSegment
(
	const Point& point,
	const Vector& camberDirection,
	const Vector& inwardNormal
) const noexcept
{
	double alpha
	{
		pi - angleBetween(camberDirection, inwardNormal)
	};
	double l	// bezier polygon segment length
	{
		chord_.value() / (1.0 + std::cos(alpha))
	};

	Pointvector points;

	points.push_back(point);		// polygon start point
	points.emplace_back				// polygon central point
	(
		point + camberDirection * l
	);
	points.emplace_back				// polygon end point
	(
		point + (camberDirection - inwardNormal) * l
	);

	return points;
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ProfileHexMeshGenerator::ProfileHexMeshGenerator(const input::Registry& reg)
:
	BaseType {reg},
	smootherIter_
	{
		reg.cref<input::SmootherIter>()
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Uptr<geometry::Volume> ProfileHexMeshGenerator::generate
(
	const design::Profile& profile
) const
{
	Uptr<geometry::Volume> mesh
	{
		std::make_unique<geometry::Volume>
		(
			geometry::operators::Extrude {}
			(
				constructSection
				(
					constructBoundary(profile)
				),
				-Vector::zAxis()	// (-) to avoid having to flip the base normal
			)
		)
	};

	geometry::interface::GmshGenerate();

	return mesh;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
