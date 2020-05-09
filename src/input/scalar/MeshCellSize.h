/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::MeshCellSize

Description
	Class MeshCellSize.

SourceFiles
	MeshCellSize.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_MESH_CELL_SIZE_H
#define INPUT_MESH_CELL_SIZE_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class MeshCellSize Declaration
\*---------------------------------------------------------------------------*/

class MeshCellSize final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"MeshCellSize"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit MeshCellSize(const Float f);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
