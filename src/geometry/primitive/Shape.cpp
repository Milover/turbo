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


void Shape::sync() noexcept
{
	if (!sync_)
		gmsh::model::geo::synchronize();
}


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

Shape::Shape(const std::pair<int, int> dimTag) noexcept
:
	dimTag_ {dimTag}
{
	sync_ = false;
}


Shape::Shape(const Shape& shape) noexcept
:
	dimTag_ {shape.dimTag_.first, shape.copy()}
{
	sync_ = false;
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Shape::~Shape() noexcept
{
	remove();

	sync_ = false;
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

std::pair<int, int> Shape::getDimTag() const noexcept
{
	return dimTag_;
}


Vectorpair<double> Shape::getBoundingBox() const noexcept
{
	sync();

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


void Shape::setSync(const bool sync) noexcept
{
	sync_ = sync;
}


bool Shape::isSync() noexcept
{
	return sync_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
