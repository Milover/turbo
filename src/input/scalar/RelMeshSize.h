/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::RelMeshSize

Description
	Class RelMeshSize.

	Ratio of average mesh cell size to chord.

	Defaults to 0.01.

SourceFiles
	RelMeshSize.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_REL_MESH_SIZE_H
#define INPUT_REL_MESH_SIZE_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class RelMeshSize Declaration
\*---------------------------------------------------------------------------*/

class RelMeshSize final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"RelMeshSize"};


	// Constructors

		//- Default constructor
		RelMeshSize() noexcept;

		//- Construct from a Integer,
		//  no aditional checking required
		explicit RelMeshSize(const Float f);


	// Member functions

		//- Get object name
		String getName() const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
