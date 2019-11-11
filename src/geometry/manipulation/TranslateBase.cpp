/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <stdexcept>

#include "gmsh.h"

#include "Point.h"
#include "TranslateBase.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<typename... T>
void TranslateBase<T...>::setVector(const Vector& vector) noexcept
{
	vector_.reset
	(
		new Vector {vector}
	);
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

template<typename... T>
TranslateBase<T...>::~TranslateBase()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename... T>
void TranslateBase<T...>::manipulate(const Vectorpair<int>& dimTags) const
{
	if (!vector_)
		throw std::runtime_error
		(
			"turbo::geometry::TranslateBase::"
			"manipulate(const turbo::Vectorpair&): "
			"Translation vector unset"
		);

	gmsh::model::geo::translate
	(
		dimTags,
		vector_->x,
		vector_->y,
		vector_->z
	);
}


template<typename... T>
bool TranslateBase<T...>::isSet() const noexcept
{
	return static_cast<bool>(vector_);
}


// * * * * * * * * * * * * * Class Specializations * * * * * * * * * * * * * //

template class TranslateBase<Vector>;

template class TranslateBase<Point, Point>;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
