/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::CarterDeviation

Description
	Class CarterDeviation.

	An empirical expression for computing the deviation angle, for more
	information see \cite{}.

	The deviation $\delta$ is computed from the following expression:

	\[
		\delta = \frac{m \theta}{\sqrt{\sigma}}
	\]

	where $\theta$ is the camber angle in \si{\degree}, $\sigma$ is the
	solidity and $m$ is defined as:

	\[
		m = 0.23 \left(2 \cdot \frac{a}{c} \right)^2 + 0.002 * \beta_2
	\]

	where $\frac{a}{c}$ is the position of maximum camber given as percent of
	chord and $\beta_2$ is the fluid outlet angle.

SourceFiles
	CarterDeviation.cpp

\*---------------------------------------------------------------------------*/

#ifndef CARTER_DEVIATION_H
#define CARTER_DEVIATION_H

#include "ComponentBase.h"
#include "DeviationMethodBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class CarterDeviation Declaration
\*---------------------------------------------------------------------------*/

class CarterDeviation
:
	public DeviationMethodBase
{
public:

	// Constructors

		//- Default constructor
		CarterDeviation() = default;


	//- Destructor
	~CarterDeviation() = default;


	// Member functions

		//- Compute deviation in degrees
		double compute(const ComponentBase& component) const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
