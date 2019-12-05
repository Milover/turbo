/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::McKenzieDeviation

Description
	Class McKenzieDeviation.

	An empirical expression for computing the deviation angle, for more
	information see \cite{}.

	For hub-tip ratios greater than 0.8 the deviation $\delta$ is computed
	from the following expression:

	\[
		\delta = ( 2 + \theta / 3 ) \sigma^{-1/3}
	\]

	where $\theta$ is the camber angle in \si{\degree}, $\sigma$ is the
	solidity. For hub-tip lower hub-tip ratios the deviation is computed
	from the following expression:

	\[
		\delta = ( 1.1 + 0.31 \theta ) \sigma^{-1/3}
	\]

	Note that these expressions were derived from experimental data from
	measurements taken on low-speed compressor cascades with cambered airfoils
	using circular arcs as camber lines.

SourceFiles
	McKenzieDeviation.cpp

\*---------------------------------------------------------------------------*/

#ifndef MCKENZIE_DEVIATION_H
#define MCKENZIE_DEVIATION_H

#include "ComponentBase.h"
#include "DeviationMethodBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class McKenzieDeviation Declaration
\*---------------------------------------------------------------------------*/

class McKenzieDeviation
:
	public DeviationMethodBase
{
public:

	// Constructors

		//- Default constructor
		McKenzieDeviation() = default;


	//- Destructor
	~McKenzieDeviation() = default;


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
