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
		Vectorpair<int> {dimTag_},
		true	// recursive
	);
}


int Shape::copy() const noexcept
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

Shape::Shape(const std::pair<int, int> dimTag) noexcept
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


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Shape::sync() noexcept
{
	if (sync_)
		return;

	gmsh::model::occ::synchronize();
	sync_ = true;
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


std::pair<int, int> Shape::getDimTag() const noexcept
{
	return dimTag_;
}


Vectorpair<int> Shape::getBoundary() const noexcept
{
	Shape::sync();
	
	Vectorpair<int> outDimTags;

	gmsh::model::getBoundary
	(
		Vectorpair<int> {getDimTag()},
		outDimTags
	);

	return std::move(outDimTags);
}


Vectorpair<double> Shape::getBoundingBox() const noexcept
{
	Shape::sync();

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

	return Vectorpair<double>
	{
		std::make_pair(xmin, xmax),
		std::make_pair(ymin, ymax),
		std::make_pair(zmin, zmax)
	};
}


bool Shape::isEmpty() const noexcept
{
	return empty_;
}


bool Shape::isSync() noexcept
{
	return sync_;
}


void Shape::setSync(const bool sync) noexcept
{
	sync_ = sync;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
