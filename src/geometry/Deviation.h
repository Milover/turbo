/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Deviation

Description
	Class Deviation

SourceFiles
	Deviation.cpp

\*---------------------------------------------------------------------------*/

#ifndef DEVIATION_H
#define DEVIATION_H

#include <memory>

#include "ComponentBase.h"
#include "DeviationMethodBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Deviation Declaration
\*---------------------------------------------------------------------------*/

class Deviation
{
private:

	// Private data

		std::unique_ptr<DeviationMethodBase> method_;


public:

	// Constructors

		//- Default constructor
		Deviation(const Stringmap<>& input);

		//- Move constructor
		Deviation(Deviation&&) = default;


	//- Destructor
	~Deviation() = default;


	// Member functions

		//- Compute deviation in degrees
		double compute(const ComponentBase& component) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
