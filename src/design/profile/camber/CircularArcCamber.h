/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::CircularArcCamber

Description
	Class CircularArcCamber declaration.

	Generates a circular arc camber line. The circular arc is centered with
	respect to the chord i.e. the position of max camber is always at
	50% of the chord.

SourceFiles
	CircularArcCamber.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_CIRCULAR_ARC_CAMBER_H
#define DESIGN_CIRCULAR_ARC_CAMBER_H

#include "CamberGeneratorBase.h"
#include "Error.h"
#include "Registry.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
					Class CircularArcCamber Declaration
\*---------------------------------------------------------------------------*/

class CircularArcCamber final
:
	public CamberGeneratorBase
{
private:

	// Private data

		Float yOffset_;


protected:

	// Member functions

		//- Compute camber ordinate at a 'x'
		Float computeY(const Float x) const noexcept override;


public:

	// Public data

		inline static const String name {"CircularArcCamber"};


	// Constructors

		//- Construct from a registry
		explicit CircularArcCamber(const input::Registry& reg);


	// Member functions

		//- Get inlination angle at 'x' in radians
		Float inclination(const Float x) const noexcept(ndebug) override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
