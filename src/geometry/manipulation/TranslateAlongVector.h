/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::TranslateAlongVector

Description
	Class TranslateAlongVector

SourceFiles
	TranslateAlongVector.cpp

\*---------------------------------------------------------------------------*/

#ifndef TRANSLATE_ALONG_VECTOR_H
#define TRANSLATE_ALONG_VECTOR_H

#include "TranslateBase.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class TranslateAlongVector Declaration
\*---------------------------------------------------------------------------*/

class TranslateAlongVector final
:
	public TranslateBase<Vector>
{
public:

	// Constructors

		//- Default constructor
		TranslateAlongVector() = default;

		//- Disallow copy construction
		TranslateAlongVector(const TranslateAlongVector&) = delete;


	//- Destructor
	~TranslateAlongVector();


	// Member functions

		//- Set translation vector
		void setParameters(const Vector& vector) noexcept override;


	// Member operators

		//- Disallow assignment
		TranslateAlongVector& operator=(const TranslateAlongVector&) = delete;


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
