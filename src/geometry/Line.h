/*---------------------------------------------------------------------------*\

Header

-------------------------------------------------------------------------------
License

Class
	turbo::geometry::Line

Description
	Line class

SourceFiles
	Line.cpp

\*---------------------------------------------------------------------------*/

#ifndef LINE_H
#define LINE_H

#include "gmsh.h"
#include "Shape.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// Forward declarations

/*---------------------------------------------------------------------------*\
						Class Line Declaration
\*---------------------------------------------------------------------------*/

class Line
:
	public Shape
{
private:

	// Private data


	// Member functions
	

protected:

	// Protected data


	// Member functions

		//- Construct Line geometry
		virtual int construct
		(
			const int startTag,
			const int endTag
		) const;


public:
	
	// Constructors
		
		//- Construct from copies of two Points
		Line
		(
			Point start,
			Point end
		);

		//- Construct from a Line
		Line(const Line&);


	//- Destructor
	virtual ~Line();


	// Member functions

		//- Get Line length
		virtual double getLength() const;


	// Member operators
	
		//- Disallow assignment
		Line& operator=(const Line&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
