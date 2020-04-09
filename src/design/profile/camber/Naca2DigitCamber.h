/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::Naca2DigitCamber

Description
	Class Naca2DigitCamber declaration.
	For more information on the generation procedure see \cite{}.

	Note the conventional limit of 0.09% of chord for the maximum camber
	is not respected, instead the maximum camber position is fixed at
	0.5% of chord and the maximum camber varies freely so that the requested
	camber angle is satisfied.

SourceFiles
	Naca2DigitCamber.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_NACA_2_DIGIT_CAMBER_H
#define DESIGN_NACA_2_DIGIT_CAMBER_H

#include "CamberGeneratorBase.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
					Class Naca2DigitCamber Declaration
\*---------------------------------------------------------------------------*/

class Naca2DigitCamber final
:
	public CamberGeneratorBase
{
private:

	// Private data

		maxCamber_;
		maxCamberPosition_ {0.4};
			// TODO: implement search for optimal maxCamberPosition_

	// Member functions

		//- Compute max camber for a given
		//  camber angle and max camber position
		void computeMaxCamber() const noexcept;


protected:

	// Member functions

		//- Compute camber ordinate at a 'x'
		Float computeY(const Float x) const override;


public:

	// Constructors

		//- Default constructor
		explicit Naca2DigitCamber(const Float camber);
			// TODO: clean up a bit


	// Member functions

		//- Get inlination angle at 'x' in radians
		Float inclination(const Float x) const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
