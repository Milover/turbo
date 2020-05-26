/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshLoft

Description
	GmshLoft class

SourceFiles
	GmshLoft.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_LOFT_H
#define INTERFACE_GMSH_LOFT_H

#include <vector>

#include "Curve.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshLoft Declaration
\*---------------------------------------------------------------------------*/

struct GmshLoft
{
	using Curvevector = Sptrvector<geometry::Curve>;

	//- Create a loft
	[[nodiscard]] std::vector<std::size_t> operator()
	(
		const Curvevector& curves
	) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
