/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::DeviationMethodBase

Description
	Abstract base class for other deviation method classes

\*---------------------------------------------------------------------------*/

#ifndef DEVIATION_METHOD_BASE_H
#define DEVIATION_METHOD_BASE_H

#include "ComponentBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class DeviationMethodBase Declaration
\*---------------------------------------------------------------------------*/

class DeviationMethodBase
{
protected:

	// Constructors

		//- Default constructor
		DeviationMethodBase() = default;


public:

	// Constructors

		//- Copy constructor
		DeviationMethodBase(const DeviationMethodBase&) = default;

		//- Move constructor
		DeviationMethodBase(DeviationMethodBase&&) = default;


	//- Destructor
	virtual ~DeviationMethodBase() = default;


	// Member functions

		//- Compute deviation in degrees
		virtual double compute(const ComponentBase& component) const = 0;


	// Member operators

		//- Assignment operator
		DeviationMethodBase& operator=(const DeviationMethodBase&) = default;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
