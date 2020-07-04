/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include "BoundaryLayerField.h"

#include "Curve.h"
#include "Error.h"
#include "General.h"
#include "GmshAddField.h"
#include "GmshSetBLMesh.h"
#include "GmshSetOptionNumber.h"
#include "InputRegistry.h"
#include "Point.h"
#include "Registry.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

BoundaryLayerField::BoundaryLayerField(const input::Registry& reg)
{
	auto returnTag {interface::GmshAddField {}(this)};
	assert(returnTag == tag());

	// set characteristics
	input::BLFirstCellHeight height
	{
		reg.cref<input::InletVelocity>(),
		reg.cref<input::BladeVelocity>(),
		reg.cref<input::Chord>(),
		reg.cref<input::DynamicViscosity>(),
		reg.cref<input::Density>(),
		reg.cref<input::YPlus>()
	};
	input::BLGrowthRate rate
	{
		reg.cref<input::BLGrowthRate>()
	};
	input::MeshCellSize size
	{
		reg.cref<input::Chord>(),
		reg.cref<input::RelMeshSize>()
	};
	input::BLThickness thickness
	{
		size,
		height,
		reg.cref<input::BLTransitionRatio>(),
		rate
	};
//	input::BLThickness thickness
//	{
//		height,
//		rate,
//		reg.cref<input::BLNumberOfLayers>()
//	};
	interface::GmshSetOptionNumber {}
	(
		"Mesh.BoundaryLayerFanPoints",
		reg.cref<input::NumberOfCamberPoints>().value() / fanFactor_
	);

	setValue("ratio",				rate.value());
	setValue("hwall_n",				height.value());
	setValue("thickness",			thickness.value());
	setValue("hfar",				size.value());
	setValue("Quads",				1.0);
	setValue("IntersectMetrics",	0.0);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void BoundaryLayerField::setField() noexcept(ndebug)
{
	if (tag() == 0)
		error(FUNC_INFO, "field doesn't exist");

	Floatvector edges;
	Floatvector corners;

	edges.reserve(edges_.size());
	corners.reserve(corners_.size());

	for (auto& e : edges_)
		edges.emplace_back
		(
			static_cast<Float>(e->tag())	// :)
		);

	for (auto& c : corners_)
		corners.emplace_back
		(
			static_cast<Float>(c->tag())	// :)
		);

	setValue("EdgesList", edges);
	setValue("FanNodesList", corners);

	interface::GmshSetBLMesh {}(this);

	set_ = true;
}


void BoundaryLayerField::setCorners
(
	const Sptrvector<geometry::Point>& points
) noexcept
{
	corners_.clear();
	corners_.reserve(points.size());

	for (auto& p : points)
		corners_.emplace_back(p);
}


void BoundaryLayerField::setEdges
(
	const Sptrvector<geometry::Curve>& curves
) noexcept
{
	edges_.clear();
	edges_.reserve(curves.size());

	for (auto& c : curves)
		edges_.emplace_back(c);
}


String BoundaryLayerField::type() const noexcept
{
	return type_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
