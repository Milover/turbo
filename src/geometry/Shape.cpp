/*---------------------------------------------------------------------------*\

Header

-------------------------------------------------------------------------------
License

\*---------------------------------------------------------------------------*/

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Axis.h"
#include "gmsh.h"
#include "Shape.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Shape::remove() const
{
	gmsh::model::occ::remove
	(
		Vectorpair<int> {dimTag_},
		true	// recursive
	);
}


int Shape::copy() const
{
	Vectorpair<int> outDimTags;

	gmsh::model::occ::copy
	(
		Vectorpair<int> {dimTag_},
		outDimTags
	);

	return outDimTags.front().second;
}


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

Shape::Shape(const std::pair<int, int> dimTag)
:
	dimTag_ {dimTag}
{}


Shape::Shape(const Shape& shape)
:
	dimTag_ {shape.dimTag_.first, shape.copy()}
{}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Shape::~Shape()
{
	remove();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

std::pair<int, int> Shape::getDimTag() const
{
	return dimTag_;
}


void Shape::getBoundary(Vectorpair<int>& dimTags) const
{
	gmsh::model::getBoundary
	(
		Vectorpair<int> {dimTag_},
		dimTags,
		false,		// combined
		true		// oriented
	);
}


Vectorpair<double> Shape::getBoundingBox() const
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


std::vector<double> Shape::getCenterOfMass() const
{
	std::vector<double> centerOfMass (3);

	gmsh::model::occ::getCenterOfMass
	(
		dimTag_.first,
		dimTag_.second,
		centerOfMass[toUnderlying(Axis::X)],
		centerOfMass[toUnderlying(Axis::Y)],
		centerOfMass[toUnderlying(Axis::Z)]
	);

	return centerOfMass;
}


std::string Shape::getName() const
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


void Shape::setName(const std::string& name)
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
