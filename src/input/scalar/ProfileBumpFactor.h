/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::ProfileBumpFactor

Description
	Class ProfileBumpFactor.

SourceFiles
	ProfileBumpFactor.cpp

	Controls the weighting of the profile contour mesh. A value of 1.0 results
	in a uniform 1D mesh, while smaller values result in more points towards
	the ends of the profile.

	Defaults to 0.05.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_PROFILE_BUMP_FACTOR_H
#define INPUT_PROFILE_BUMP_FACTOR_H

#include "General.h"
#include "LimitedValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class ProfileBumpFactor Declaration
\*---------------------------------------------------------------------------*/

class ProfileBumpFactor final
:
	public LimitedValue<Float, 0, 1>
{
public:

	// Public static data

		inline static const String name {"ProfileBumpFactor"};


	// Constructors

		//- Default constructor
		ProfileBumpFactor() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit ProfileBumpFactor(const Float f);


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
