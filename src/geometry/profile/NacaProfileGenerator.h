/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::NacaProfileGenerator

Description
	Class NacaProfileGenerator declaration.
	Currently only the 4-digit (and 4-digit modified) series NACA profiles are
	supported, for more information on the generation procedure see \cite{}.
	Valid series designations are:

		4-digit:			4412
		4-digit modified:	4412-63
	
	The first digit is the max camber as \% of chord;
	The second digit is the position of max camber as 10\% of chord;
	The third and fourth digits are the max thickness as \% of chord;
	The fifth digit is the leading edge radius index;
	The sixth digit is the position of max thickness as 10\% of chord;

	Note that the 4-digit series is a special case of the 4-digit modified
	series where the radius index and max thickness position are set to ``63''
	i.e. ``4412'' and ``4412-63'' refer to the same profile.

	The coefficients in the two equations used to determine the profile
	ordinates were determined for a ``mp20'' profile (max thickness equal to
	20\% of chord) and must be scaled by

	\[
		\frac{t}{c} * \frac{1}{0.2} = 5 * \frac{t}{c}
	\]
	
	where $t$ is max thickness and $c$ is chord length, to obtain ordinates
	of profiles with a thickness-chord ratio other than 0.2.

	The number of evaluation (cambe line) points is set via the
	``numberOfPoints'' keyword and must be an integer number. The type of
	scaling can be specified via the ``spacingType'' keyword. Currently
	``linear'' and ``cosine'' spacing are available. Note that cosine spacing
	is recommended as it gives appropriate resoultions (geometry and mesh) at
	both the leading and the trailing edge. The default values for the
	``numberOfPoints'' and ``spacingType'' are 40 and ``cosine'' respectively.

	NOTE:
		Currently only symmetrical profiles are supported (eg. ``0012'').

SourceFiles
	NacaProfileGenerator.cpp

\*---------------------------------------------------------------------------*/

#ifndef NACA_PROFILE_GENERATOR_H
#define NACA_PROFILE_GENERATOR_H

#include <map>
#include <string>
#include <vector>

#include "ProfileGeneratorBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class NacaProfileGenerator Declaration
\*---------------------------------------------------------------------------*/

class NacaProfileGenerator final
:
	public ProfileGeneratorBase
{
private:

	// Private data
	
	double a_[4];
	double d_[4];

	static const std::map<int, double> d1Table_;
	static const double scale_;
	static const double chord_;

	double m_;		// 1st digit / 100
	double p_;		// 2nd digit / 10
	double t_;		// 3rd & 4th digit / 100
	double I_;		// 5th digit
	double M_;		// 6th digit / 10

	int spacingType_;
	double spacingIncrement_;

	enum spacing_
	{
		LINEAR,
		COSINE
	};

	Vectorpair<double> camberLine_;


	// Member functions

		//- Parse profile series
		void parseSeries(const std::string& series);

		//- Set spacing increment
		void setSpacingIncrement(const int numberOfPoints);

		//- Compute $a_0$ coefficient
		void computeA0();

		//- Look up $d_1$ coefficient
		void lookUpD1();

		//- Compute $d_2$ coefficient
		void computeD2();

		//- Compute $d_3$ coefficient
		void computeD3();

		//- Scale coefficients
		void scaleCoefficients();

		//- Generate camber line coordinates
		void generateCamberLine();

		//- Compute camber abscissa at a given point
		double computeCamberX(const double x) const;

		//- Compute camber ordinate at a given point
		double computeCamberY(const double x) const;

		//- Compute profile thickness at ``x''
		double computeThickness(const double x) const;

		//- Compute camber inclination at ``x''
		double computeInclination(const double x) const;

		//- Compute surface x-coordinate offset
		double computeDX
		(
			const double thickness,
			const double inclination
		) const;

		//- Compute surface y-coordinate offset
		double computeDY
		(
			const double thickness,
			const double inclination
		) const;


protected:

	// Member functions

		//- Parse input data
		void parseInput(const Stringmap& input) override;


public:
	
	// Constructors

		//- Default constructor
		NacaProfileGenerator(const Stringmap& input);
	
		//- Copy constructor
		NacaProfileGenerator(const NacaProfileGenerator&) = default;


	//- Destructor
	virtual ~NacaProfileGenerator();


	// Member functions

		//- Generate profile coordinates
		void generate() override;


	// Member operators

		//- Disallow assignment
		NacaProfileGenerator& operator=(const NacaProfileGenerator&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
