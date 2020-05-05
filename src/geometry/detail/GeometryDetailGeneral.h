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

// * * * * * * * * * * * * * * * Type Traits * * * * * * * * * * * * * * * * //

//- Returns the base class of a geometry type,
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
