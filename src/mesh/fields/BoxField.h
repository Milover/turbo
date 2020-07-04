/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::BoxField

Description
	BoxField class.

SourceFiles
	BoxField.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_FIELDS_BOX_FIELD_H
#define MESH_FIELDS_BOX_FIELD_H

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
						Class BoxField Declaration
\*---------------------------------------------------------------------------*/

class BoxField
:
	public SizeField
{
private:

	// Private data

		inline static const String type_ {"Box"};


public:

	// Constructors

		//- Construct from a registry,
		//	scale computed mesh size by factor
		BoxField
		(
			const input::Registry& reg,
			const Float factor = 1.0
		);

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
