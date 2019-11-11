/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Translate

Description
	Class Translate for translation of geometry and a base class for more
	specialized translation classes.

SourceFiles
	Translate.cpp

\*---------------------------------------------------------------------------*/

#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "ManipulatorBase.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Translate Declaration
\*---------------------------------------------------------------------------*/

class Translate
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
