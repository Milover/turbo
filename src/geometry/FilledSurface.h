/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::FilledSurface

Description
	FilledSurface class

SourceFiles
	FilledSurface.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_FILLED_SURFACE_H
#define GEOMETRY_FILLED_SURFACE_H

#include <utility>

#include "Curve.h"
#include "General.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class FilledSurface Declaration
\*---------------------------------------------------------------------------*/

class FilledSurface final
:
	public Surface
{
private:

	// Member functions

		//- Construct surface geometry
		void construct() noexcept;


public:

	// Constructors

		//- Construct from curves forming a closed loop
		template<typename... Curves>
		FilledSurface(Curves&&... cs);

		//- Copy constructor
		FilledSurface(const FilledSurface&) = delete;

		//- Copy constructor
		FilledSurface(FilledSurface&&) = default;


	//- Destructor
	~FilledSurface() = default;


	// Member operators

		//- Disallow copy assignment
		FilledSurface& operator=(const FilledSurface&) = delete;

		//- Disallow copy assignment
		FilledSurface& operator=(FilledSurface&&) = delete;

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename... Curves>
FilledSurface::FilledSurface(Curves&&... cs)
:
	Surface
	{
		std::forward<Curves>(cs)...
	}
{
	construct();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
