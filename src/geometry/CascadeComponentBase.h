/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::CascadeComponentBase

Description
	Abstract base class for cascade components.

SourceFiles
	CascadeComponentBase.cpp

\*---------------------------------------------------------------------------*/

#ifndef CASCADE_COMPONENT_BASE_H
#define CASCADE_COMPONENT_BASE_H

#include <memory>

#include "Point.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class CascadeComponentBase  Declaration
\*---------------------------------------------------------------------------*/

class CascadeComponentBase
{
protected:

	// Protected data
	
		Ptrvector<Point> points_;


	// Constructors
		
		//- Default constructor
		CascadeComponentBase() = default;
	

	// Member functions

		//- Generate points from input map
		virtual void generatePoints(const Stringmap& input) = 0;

		//- Get vector of dimTags of underlying geometry
		virtual Vectorpair<int> getDimTags() const noexcept;


public:
	
	// Constructors

		//- Copy constructor
		CascadeComponentBase(const CascadeComponentBase&);


	//- Destructor
	virtual ~CascadeComponentBase() = default;


	// Member functions

		//- Build geometry
		virtual void build() = 0;

		//- Get geometric center
		Point getCenter() const noexcept;

		//- Translate along vector
		void translate(const Vector& vector) const noexcept;

		//- Align geometric center with a point
		void centerOnPoint(const Point& point) const noexcept;

		//- Rotate around geometric center by 'angle' radians
		void rotate(const double angle) const noexcept;

		//- Scale uniformly about geometric center
		void scale(const double factor) const noexcept;


	// Member operators
	
		//- Disallow assignment
		CascadeComponentBase& operator=(const CascadeComponentBase&) = delete;


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
