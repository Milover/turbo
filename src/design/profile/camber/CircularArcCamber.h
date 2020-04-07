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

#ifndef CIRCULAR_ARC_CAMBER_H
#define CIRCULAR_ARC_CAMBER_H

#include "CamberGeneratorBase.h"
#include "Utility.h"

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

		double offset_;


protected:

	// Member functions

		//- Build input map
		void buildInputMap() noexcept override;

		//- Compute camber parameters to satisfy
		//  a given camber angle
		void computeParameters(const double camberAngle) noexcept override;

		//- Compute camber ordinate at a ``x''
		double computeY(const double x) const override;


public:

	// Constructors

		//- Default constructor
		CircularArcCamber(const Stringmap<>& input);

		//- Move constructor
		CircularArcCamber(CircularArcCamber&&) = default;


	//- Destructor
	~CircularArcCamber() = default;


	// Member functions

		//- Get inlination angle at ``x'' in degrees
		double getInclinationAt(const double x) const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
