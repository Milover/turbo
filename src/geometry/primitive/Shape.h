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

#ifndef SHAPE_H
#define SHAPE_H

#include <utility>

#include "Utility.h"

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

		const std::pair<int, int> dimTag_;
		bool empty_;
		static bool sync_;


	// Member functions

		//- Remove Shape geometry
		void remove() const noexcept;

		//- Copy Shape geometry and return tag
		int copy() const noexcept;


protected:

	// Constructors

		//- Construct from tag
		Shape(const std::pair<int, int> dimTag) noexcept;

		//- Copy constructor
		Shape(const Shape&) noexcept;

		//- Move constructor
		Shape(Shape&&) noexcept;


	// Member functions

		//- Synchronize geometry
		static void sync() noexcept;


public:

	//- Destructor
	virtual ~Shape() noexcept;


	// Member functions

		//- Release ownership of underlying geometry
		void release() noexcept;

		//- Return Shape dimTag
		std::pair<int, int> getDimTag() const noexcept;

		//- Get boundary dimTags
		Vectorpair<int> getBoundary() const noexcept;

		//- Get bounding box
		Vectorpair<double> getBoundingBox() const noexcept;

		//- Check if empty
		bool isEmpty() const noexcept;

		//- Check if synchronized
		static bool isSync() noexcept;

		//- Set synchronization
		static void setSync(const bool sync) noexcept;


	// Member operators

		//- Disallow assignment
		Shape& operator=(const Shape&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
