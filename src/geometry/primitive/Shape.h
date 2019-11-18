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
		static bool sync_;


	// Member functions

		//- Remove Shape geometry
		void remove() const noexcept;

		//- Copy Shape geometry and return tag
		int copy() const noexcept;

		//- Synchronize geometry
		static void sync() noexcept;


protected:

	// Constructors

		//- Construct from tag
		Shape(const std::pair<int, int> dimTag) noexcept;

		//- Construct from a Shape
		Shape(const Shape&) noexcept;


public:

	//- Destructor
	virtual ~Shape() noexcept;


	// Member functions

		//- Return Shape dimTag
		std::pair<int, int> getDimTag() const noexcept;

		//- Get bounding box
		Vectorpair<double> getBoundingBox() const noexcept;

		//- Set synchronization
		static void setSync(const bool sync) noexcept;

		//- Check if synchronized
		static bool isSync() noexcept;


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
