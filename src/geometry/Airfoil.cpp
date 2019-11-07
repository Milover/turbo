/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <memory>
#include <stdexcept>

#include "Airfoil.h"
#include "Point.h"
#include "ProfileGeneratorInterface.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Airfoil::Airfoil
(
	const ProfileGeneratorInterface& generator
)
{
	for (int i {0}; i < generator.getSize(); i++)
	{
		surfacePoints_.push_back
		(
			std::make_pair
			(
				std::make_unique<Point>
				(
					generator.getUpperPointAt(i)
				),
				std::make_unique<Point>
				(
					generator.getLowerPointAt(i)
				)
			)
		);
	}
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Airfoil::~Airfoil()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //