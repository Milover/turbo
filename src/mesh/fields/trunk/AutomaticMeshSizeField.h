/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::AutomaticMeshSizeField

Description
	AutomaticMeshSizeField class.

	NOTE:
		gmsh has to be compiled with HXT and P4EST to use automaticMeshSizeField


SourceFiles
	AutomaticMeshSizeField.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_FIELDS_AUTOMATIC_MESH_SIZE_FIELD_H
#define MESH_FIELDS_AUTOMATIC_MESH_SIZE_FIELD_H

#include "Error.h"
#include "General.h"
#include "Registry.h"
#include "SizeField.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

/*---------------------------------------------------------------------------*\
				Class AutomaticMeshSizeField Declaration
\*---------------------------------------------------------------------------*/

class AutomaticMeshSizeField
:
	public SizeField
{
private:

	// Private data

		inline static const String type_ {"AutomaticMeshSizeField"};


public:

	// Constructors

		//- Construct form a registry
		AutomaticMeshSizeField(const input::Registry& reg);


	// Member functions

		//- Set field
		void setField() noexcept(ndebug) override;

		//- Get type
		[[nodiscard]] String type() const noexcept override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
