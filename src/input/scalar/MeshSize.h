/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::MeshSize

Description
	Class MeshSize.

	Target mesh cell count.

	Defaults to 40000.

SourceFiles
	MeshSize.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_MESH_SIZE_H
#define INPUT_MESH_SIZE_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class MeshSize Declaration
\*---------------------------------------------------------------------------*/

class MeshSize final
:
	public PositiveValue<Integer>
{
public:

	// Public static data

		inline static const String name {"MeshSize"};


	// Constructors

		//- Default constructor
		MeshSize() noexcept;

		//- Construct from a Integer,
		//  no aditional checking required
		explicit MeshSize(const Integer i);


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
