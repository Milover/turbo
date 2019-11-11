/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <memory>

#include "Airfoil.h"
#include "Point.h"
#include "ProfileGeneratorInterface.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Airfoil::generatePoints(const Stringmap& input)
{
	ProfileGeneratorInterface generator {input};

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


Vectorpair<int> getDimTags() const noexcept override
{

}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Airfoil::Airfoil
(
	const Stringmap& input
)
{
	generatePoints(input);
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Airfoil::~Airfoil()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
