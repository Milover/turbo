/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::compute::NewtonRapshon

Description
	Class NewtonRaphson

SourceFiles
	NewtonRaphson.cpp

\*---------------------------------------------------------------------------*/

#ifndef COMPUTE_NEWTON_RAPHSON_H
#define COMPUTE_NEWTON_RAPHSON_H

#include <cmath>
#include <iomanip>
#include <iostream>
#include <type_traits>

#include "Error.h"
#include "General.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace compute
{

/*---------------------------------------------------------------------------*\
					Class NewtonRaphson Declaration
\*---------------------------------------------------------------------------*/

struct NewtonRaphson
{
	// Data

		std::size_t maxIter {1000};
		Float tol {1e-9};


	// Member operators

		//- Call operator
		template
		<
			typename X,
			typename F,
			typename DFDX,
			typename = std::enable_if_t
			<
				std::is_floating_point_v<X>
			 && std::is_invocable_v<removeCVRef_t<F>, X>
			 && std::is_invocable_v<removeCVRef_t<DFDX>, X>
			>
		>
		X operator()
		(
			const X& x,
			F&& f,
			DFDX&& dfdx
		) const;

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename X, typename F, typename DFDX, typename>
X NewtonRaphson::operator()
(
	const X& x,
	F&& f,
	DFDX&& dfdx
) const
{
	X xOld {x};
	X xNew {};

	std::size_t iter {0};
	for (; iter < maxIter; ++iter)
	{
		xNew = xOld - f(xOld) / dfdx(xOld);

		if
		(
			isLessOrEqual(std::abs(xOld - xNew), tol)
		 || std::isnan(xNew)
		)
			break;

		xOld = xNew;
	}

	if constexpr (ndebug)
	{
		if (iter == maxIter)
			std::cerr << "WARNING: "
						 "Newton-Raphson reached maxIter without convergence\n";
	}

	return xNew;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compute
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
