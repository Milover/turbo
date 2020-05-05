/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::interface::GmshBase

Description
	GmshBase class

SourceFiles
	GmshBase.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_INTERFACE_GMSH_BASE_H
#define GEOMETRY_INTERFACE_GMSH_BASE_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshBase Definition
\*---------------------------------------------------------------------------*/

class GmshBase
{
protected:

	// Private data

		inline static thread_local bool sync_ {false};


	// Constructors

		//- Default constructor
		GmshBase() noexcept;


public:

	// Member functions

		//- Return synchronization state
		static bool sync() noexcept;

		//- Synchronize if unsynchronized
		static void synchronize() noexcept;

		//- Unsynchronize
		static void unsynchronize() noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
