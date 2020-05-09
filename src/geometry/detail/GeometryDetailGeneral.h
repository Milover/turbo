/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Some utilities for the geometry module

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_DETAIL_GENERAL_H
#define GEOMETRY_DETAIL_GENERAL_H

#include <type_traits>

#include "Curve.h"
#include "Entity.h"
#include "General.h"
#include "PlaceholderCurve.h"
#include "PlaceholderPoint.h"
#include "PlaceholderSurface.h"
#include "PlaceholderVolume.h"
#include "Point.h"
#include "Surface.h"
#include "Volume.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace detail
{

// * * * * * * * * * * * * * * GeometryBaseType  * * * * * * * * * * * * * * //

//- Returns the base class of a geometry type
template<typename T, Integer dimension = T::dim>
struct GeometryBaseType;


template<typename T>
struct GeometryBaseType<T, Entity0D::dim>
{
	static_assert(isEntity_v<T>);

	using type = Point;
};


template<typename T>
struct GeometryBaseType<T, Entity1D::dim>
{
	static_assert(isEntity_v<T>);

	using type = Curve;
};


template<typename T>
struct GeometryBaseType<T, Entity2D::dim>
{
	static_assert(isEntity_v<T>);

	using type = Surface;
};


template<typename T>
struct GeometryBaseType<T, Entity3D::dim>
{
	static_assert(isEntity_v<T>);

	using type = Volume;
};


template<typename T>
using GeometryBaseType_t = typename GeometryBaseType<T>::type;


// * * * * * * * * * * * * * GeometryLowerOrderType  * * * * * * * * * * * * //

//- Returns the base class of a lower order geometry type,
//	Points return themselves
template<typename T, Integer dimension = T::dim>
struct GeometryLowerOrderType;


template<typename T>
struct GeometryLowerOrderType<T, Entity0D::dim>
{
	static_assert(isEntity_v<T>);

	using type = Point;
};


template<typename T>
struct GeometryLowerOrderType<T, Entity1D::dim>
{
	static_assert(isEntity_v<T>);

	using type = Point;
};


template<typename T>
struct GeometryLowerOrderType<T, Entity2D::dim>
{
	static_assert(isEntity_v<T>);

	using type = Curve;
};


template<typename T>
struct GeometryLowerOrderType<T, Entity3D::dim>
{
	static_assert(isEntity_v<T>);

	using type = Surface;
};


template<typename T>
using GeometryLowerOrderType_t = typename GeometryLowerOrderType<T>::type;


// * * * * * * * * * * * * GeometryHigherOrderType * * * * * * * * * * * * * //

//- Returns the base class of a higher order geometry type,
//	Volumes return themselves
template<typename T, Integer dimension = T::dim>
struct GeometryHigherOrderType;


template<typename T>
struct GeometryHigherOrderType<T, Entity0D::dim>
{
	static_assert(isEntity_v<T>);

	using type = Curve;
};


template<typename T>
struct GeometryHigherOrderType<T, Entity1D::dim>
{
	static_assert(isEntity_v<T>);

	using type = Surface;
};


template<typename T>
struct GeometryHigherOrderType<T, Entity2D::dim>
{
	static_assert(isEntity_v<T>);

	using type = Volume;
};


template<typename T>
struct GeometryHigherOrderType<T, Entity3D::dim>
{
	static_assert(isEntity_v<T>);

	using type = Volume;
};


template<typename T>
using GeometryHigherOrderType_t = typename GeometryHigherOrderType<T>::type;


// * * * * * * * * * * * * GeometryPlaceholderType * * * * * * * * * * * * * //

//- Returns the placeholder class of a geometry type,
template<typename T, Integer dimension = T::dim>
struct GeometryPlaceholderType;


template<typename T>
struct GeometryPlaceholderType<T, Entity0D::dim>
{
	static_assert(isEntity_v<T>);

	using type = PlaceholderPoint;
};


template<typename T>
struct GeometryPlaceholderType<T, Entity1D::dim>
{
	static_assert(isEntity_v<T>);

	using type = PlaceholderCurve;
};


template<typename T>
struct GeometryPlaceholderType<T, Entity2D::dim>
{
	static_assert(isEntity_v<T>);

	using type = PlaceholderSurface;
};


template<typename T>
struct GeometryPlaceholderType<T, Entity3D::dim>
{
	static_assert(isEntity_v<T>);

	using type = PlaceholderVolume;
};


template<typename T>
using GeometryPlaceholderType_t = typename GeometryPlaceholderType<T>::type;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // end namespace detail
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
