/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::BezierTangential

Description
	Class BezierTangential

SourceFiles
	BezierTangential.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_SKEW_BEZIER_TANGENTIAL_H
#define DESIGN_SKEW_BEZIER_TANGENTIAL_H

#include "BezierCurve.h"
#include "Error.h"
#include "General.h"
#include "Registry.h"
#include "SkewDistributionBase.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
						Class BezierTangential Declaration
\*---------------------------------------------------------------------------*/

class BezierTangential final
:
	public SkewDistributionBase
{
private:

	using Point = Vector;

	// Private data

		input::HubRadius r_h_;
		input::ShroudRadius r_s_;
		input::TipClearance z_tip_;

		Uptr<math::BezierCurve<2>> bc_;


	// Member functions

		//- Construct the distribution
		void construct
		(
			const Float d_h,	// hub skew angle
			const Float d_s,	// shroud skew angle
			const Float rho		// relative radius
		) noexcept;


public:

	// Public data

		inline static const String name {"BezierTangential"};


	// Constructors

		//- Defaul constructor
		BezierTangential(const input::Registry& reg);


	// Member functions

		//- Apply skew to profile
		void skew(Profile& profile) const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
