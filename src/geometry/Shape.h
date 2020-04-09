/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Shape

Description
	Abstract base class for geometry objects

SourceFiles
	Shape.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_SHAPE_H
#define GEOMETRY_SHAPE_H

#include "General.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Shape Declaration
\*---------------------------------------------------------------------------*/

class Shape
{
private:

	// Private data

		const Pair<Integer> dimTag_;
		bool empty_;
		static bool sync_;


	// Member functions

		//- Remove Shape geometry
		void remove() const noexcept;

		//- Copy Shape geometry and return tag
		Integer copy() const noexcept;


protected:

	using Coordinates = Vector;


	// Constructors

		//- Construct from tag
		Shape(const Pair<Integer> dimTag) noexcept;

		//- Copy constructor
		Shape(const Shape&) noexcept;

		//- Move constructor
		Shape(Shape&&) noexcept;


public:

	//- Destructor
	virtual ~Shape() noexcept;


	// Member functions

		//- Release ownership of underlying geometry
		void release() noexcept;

		//- Return Shape dimTag
		Pair<Integer> getDimTag() const noexcept;

		//- Get boundary dimTags
		Vectorpair<Integer> getBoundary() const noexcept;

		//- Get bounding box
		Pair<Coordinates> getBoundingBox() const noexcept;

		//- Check if empty
		bool empty() const noexcept;

		//- Check if synchronized
		static bool sync() noexcept;

		//- Synchronize geometry
		static void synchronize() noexcept;


	// Member operators

		//- Disallow copy assignment
		Shape& operator=(const Shape&) = delete;

		//- Disallow move assignment
		Shape& operator=(Shape&&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
