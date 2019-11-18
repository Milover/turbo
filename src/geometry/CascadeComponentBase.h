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


public:
	
	// Constructors

		//- Copy constructor
		CascadeComponentBase(const CascadeComponentBase&);


	//- Destructor
	virtual ~CascadeComponentBase() = default;


	// Member functions

		//- Build geometry
		virtual void build() = 0;

		//- Get dimTags
		virtual Vectorpair<int> getDimTags() const noexcept;

		//- Get geometric center
		Point getCenter() const noexcept;


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
