/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::ProfileGenerator

Description
	Class ProfileGenerator

SourceFiles
	ProfileGenerator.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_PROFILE_GENERATOR_H
#define DESIGN_PROFILE_GENERATOR_H

#include <vector>

#include "CamberGenerators.h"
#include "DistributionGenerators.h"
#include "Error.h"
#include "General.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
				Class ProfileGenerator Declaration
\*---------------------------------------------------------------------------*/

class ProfileGenerator
{
private:

	using Point = Vector;


	// Private data

		Uptr<CamberGeneratorBase> cGen_;
		Uptr<DistributionGeneratorBase> dGen_;


	// Member functions

		//- Set camber type
		void createCamberGenerator
		(
			const input::CamberAngle& camber
		);

		//- Set distribution type
		void createDistributionGenerator();


public:

	// Constructors

		//- Construct from camber angle
		explicit ProfileGenerator(const input::CamberAngle& camber);


	// Member functions

		//- Generate a profile
		Vectorpair<Point> generate() const noexcept(ndebug);

		//- Get camber line inclination at 'x',
		//	x ∈ [0, 1] 0 being the LE and 1 being the TE
		Float inclination(const Float x) const noexcept;

		//- Reset
		void reset(const input::CamberAngle& camber);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
