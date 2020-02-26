/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::DeHallerCriterion

Description
	Class DeHallerCriterion

SourceFiles
	DeHallerCriterion.cpp

\*---------------------------------------------------------------------------*/

#ifndef DEHALLER_CRITERION_H
#define DEHALLER_CRITERION_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class DeHallerCriterion Declaration
\*---------------------------------------------------------------------------*/

class DeHallerCriterion
{
public:

	// Public data

		inline static constexpr double constant {0.72};


	// Constructors

		//- Default constructor
		DeHallerCriterion() = default;

		//- Copy constructor
		DeHallerCriterion(const DeHallerCriterion&) = default;

		//- Move constructor
		DeHallerCriterion(DeHallerCriterion&&) = default;


	//- Destructor
	~DeHallerCriterion() = default;


	// Member operators

		//- Assignment operator
		DeHallerCriterion& operator=(const DeHallerCriterion&) = default;

		//- Function call operator
		//  returns modified fluid outlet angle in degrees
		double operator()
		(
			const double fluidInletAngle,
			const double fluidOutletAngle
		) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
