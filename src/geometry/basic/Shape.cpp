/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <string>
#include <utility>
#include <vector>

#include "gmsh.h"

#include "Axis.h"
#include "Shape.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Shape::remove() const noexcept
{
	gmsh::model::geo::remove
	(
		Vectorpair<int> {dimTag_},
		true	// recursive
	);
}


int Shape::copy() const noexcept
{
	Vectorpair<int> outDimTags;

	gmsh::model::geo::copy
	(
		Vectorpair<int> {dimTag_},
		outDimTags
	);

	return outDimTags.front().second;
}


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

Shape::Shape(const std::pair<int, int> dimTag) noexcept
:
	dimTag_ {dimTag}
{}


Shape::Shape(const Shape& shape) noexcept
:
	dimTag_ {shape.dimTag_.first, shape.copy()}
{}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Shape::~Shape() noexcept
{
	remove();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

std::pair<int, int> Shape::getDimTag() const noexcept
{
	return dimTag_;
}


void Shape::getBoundary(Vectorpair<int>& dimTags) const noexcept
{
	gmsh::model::getBoundary
	(
		Vectorpair<int> {dimTag_},
		dimTags,
		false,		// combined
		true		// oriented
	);
}


Vectorpair<double> Shape::getBoundingBox() const noexcept
{
	Vectorpair<double> minMax (3);

	gmsh::model::getBoundingBox
	(
		dimTag_.first,
		dimTag_.second,
		minMax[toUnderlying(Axis::X)].first,
		minMax[toUnderlying(Axis::Y)].first,
		minMax[toUnderlying(Axis::Z)].first,
		minMax[toUnderlying(Axis::X)].second,
		minMax[toUnderlying(Axis::Y)].second,
		minMax[toUnderlying(Axis::Z)].second
	);

	return minMax;
}


std::string Shape::getName() const noexcept
{
	std::string name;

	gmsh::model::getEntityName
	(
		dimTag_.first,
		dimTag_.second,
		name
	);

	return name;
}


void Shape::setName(const std::string& name) noexcept
{
	gmsh::model::setEntityName
	(
		dimTag_.first,
		dimTag_.second,
		name
	);
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
