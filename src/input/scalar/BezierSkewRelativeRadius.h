/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::BezierSkewRelativeRadius

Description
	Class BezierSkewRelativeRadius.

	Relative position of midpoint knot of the Bezier curve defining the skew
	distribution. Defined as:

		rho = (r - r_h) / (r_s - r_h)
	
	where r is the radius at which the point is placed, r_h is the hub radius
	and r_s is the shroud radius.

	Defaults to 0.5.

SourceFiles
	BezierSkewRelativeRadius.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_BEZIER_SKEW_RELATIVE_RADIUS_H
#define INPUT_BEZIER_SKEW_RELATIVE_RADIUS_H

#include "General.h"
#include "LimitedValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class BezierSkewRelativeRadius Declaration
\*---------------------------------------------------------------------------*/

class BezierSkewRelativeRadius final
:
	public LimitedValue<Float, 0, 1>
{
public:

	// Public static data

		inline static const String name {"BezierSkewRelativeRadius"};


	// Constructors

		//- Default constructor
		BezierSkewRelativeRadius() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit BezierSkewRelativeRadius(const Float f);


	// Member functions

		//- Get object name
		String getName() const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
