/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Naca2DigitCamber

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

#ifndef NACA_2_DIGIT_CAMBER_H
#define NACA_2_DIGIT_CAMBER_H

#include "CamberGeneratorBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class Naca2DigitCamber Declaration
\*---------------------------------------------------------------------------*/

class Naca2DigitCamber final
:
	public CamberGeneratorBase
{
private:

	// Member functions

		//- Compute max camber for a given
		//  camber angle and max camber position
		double computeMaxCamber
		(
			const double camberAngle,
			const double maxCamberPosition
		) const noexcept;

		//- Compute max camber position for a given
		//  camber angle and max camber
		//  NOTE: this is not actually used
		double computeMaxCamberPosition
		(
			const double camberAngle,
			const double maxCamber
		) const noexcept;


protected:

	// Member functions

		//- Build input map
		void buildInputMap() noexcept override;

		//- Check values
		void check() const override;

		//- Compute camber parameters to satisfy
		//  a given camber angle
		void computeParameters(const double camberAngle) override;

		//- Compute camber ordinate at a ``x''
		double computeY(const double x) const override;

		//- Parse input
		void parse(const Stringmap<>& input) override;


public:

	// Constructors

		//- Default constructor
		Naca2DigitCamber(const Stringmap<>& input);

		//- Move constructor
		Naca2DigitCamber(Naca2DigitCamber&&) = default;


	//- Destructor
	~Naca2DigitCamber() = default;


	// Member functions

		//- Get inlination angle at ``x'' in degrees
		double getInclinationAt(const double x) const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
