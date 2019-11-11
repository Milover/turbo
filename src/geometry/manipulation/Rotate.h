/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Rotate

Description
	Class Rotate for rotation of geometry and a base class for more
	specialized rotation classes.

SourceFiles
	Rotate.cpp

\*---------------------------------------------------------------------------*/

#ifndef ROTATE_H
#define ROTATE_H

#include "ManipulatorBase.h"
#include "Point.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Rotate Declaration
\*---------------------------------------------------------------------------*/

class Rotate
:
	public ManipulatorBase<Vector>
{
public:

	// Constructors

		//- Default constructor
		Translate() = default;

		//- Disallow copy construction
		Translate(const Translate&) = delete;

		//- Construct with parameter
		Translate(const Vector& vector);


	//- Destructor
	virtual ~Translate();


	// Member functions

		//- Manipulate geometry
		virtual void manipulate
		(
			const Vectorpair<int>& dimTags
		) const override;


	// Member operators

		//- Disallow assignment
		Translate& operator=(const Translate&) = delete;


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
