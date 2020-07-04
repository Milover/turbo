/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::ConeField

Description
	ConeField class.

SourceFiles
	ConeField.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_FIELDS_CONE_FIELD_H
#define MESH_FIELDS_CONE_FIELD_H

#include "Error.h"
#include "General.h"
#include "Registry.h"
#include "SizeField.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

/*---------------------------------------------------------------------------*\
						Class ConeField Declaration
\*---------------------------------------------------------------------------*/

class ConeField
:
	public SizeField
{
private:

	// Private data

		inline static const String type_ {"Frustum"};


public:

	// Constructors

		//- Construct from a registry and some parameters,
		//	scale computed mesh size by factor, 'angle' is the cone half-angle
		//	in radians, extends to 'infinity'
		ConeField
		(
			const input::Registry& reg,
			const Vector& p1,
			const Vector& p2,
			const Float r1,
			const Float r2,
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
