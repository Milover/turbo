/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "gmsh.h"

#include "Shape.h"
#include "Utility.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * * //

bool Shape::sync_ {false};


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Shape::remove() const noexcept
{
	gmsh::model::occ::remove
	(
		Vectorpair<Integer> {dimTag_},
		true	// recursive
	);
}


Integer Shape::copy() const noexcept
{
	Vectorpair<Integer> outDimTags;

	gmsh::model::occ::copy
	(
		Vectorpair<Integer> {dimTag_},
		outDimTags
	);

	return outDimTags.front().second;
}


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

Shape::Shape(const Pair<Integer> dimTag) noexcept
:
	dimTag_ {dimTag},
	empty_ {false}
{
	sync_ = false;
}


Shape::Shape(const Shape& shape) noexcept
:
	dimTag_ {shape.dimTag_.first, shape.copy()},
	empty_ {false}
{
	sync_ = false;
}


Shape::Shape(Shape&& shape) noexcept
:
	dimTag_
	{
		std::move(shape.dimTag_)
	},
	empty_ {false}
{
	shape.release();
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Shape::~Shape() noexcept
{
	if (!empty_)
	{
		remove();
		sync_ = false;
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Shape::release() noexcept
{
	empty_ = true;
}


Pair<Integer> Shape::getDimTag() const noexcept
{
	return dimTag_;
}


Vectorpair<Integer> Shape::getBoundary() const noexcept
{
	Shape::synchronize();
	
	Vectorpair<Integer> outDimTags;

	gmsh::model::getBoundary
	(
		Vectorpair<Integer> {getDimTag()},
		outDimTags
	);

	return std::move(outDimTags);
}


Pair<Shape::Coordinates> Shape::getBoundingBox() const noexcept
{
	Shape::synchronize();

	double xmin, ymin, zmin, xmax, ymax, zmax;

	gmsh::model::getBoundingBox
	(
		getDimTag().first,
		getDimTag().second,
		xmin,
		ymin,
		zmin,
		xmax,
		ymax,
		zmax
	);

	return std::make_pair
	{
		Coordinates {xmin, ymin, zmin},
		Coordinates {xmax, ymax, zmax}
	};
}


bool Shape::empty() const noexcept
{
	return empty_;
}


bool Shape::sync() noexcept
{
	return sync_;
}


void Shape::synchronize() noexcept
{
	if (!sync_)
	{
		gmsh::model::occ::synchronize();
		sync_ = true;
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
