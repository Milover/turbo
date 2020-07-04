/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>
#include <cmath>

#include "ConeField.h"

#include "Error.h"
#include "General.h"
#include "GmshAddField.h"
#include "GmshSetBGMesh.h"
#include "Registry.h"
#include "Variables.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ConeField::ConeField
(
	const input::Registry& reg,
	const Vector& p1,
	const Vector& p2,
	const Float r1,
	const Float r2,
	const Float factor
)
{
	auto returnTag {interface::GmshAddField {}(this)};
	assert(returnTag == tag());

	input::MeshCellSize size
	{
		reg.cref<input::Chord>(),
		reg.cref<input::RelMeshSize>()
	};

	setValue("X1",			p1.x());
	setValue("Y1",			p1.y());
	setValue("Z1",			p1.z());
	setValue("X2",			p2.x());
	setValue("Y2",			p2.y());
	setValue("Z2",			p2.z());
	setValue("R1_outer",	r1);
	setValue("R2_outer",	r2);
	setValue("V1_inner",	factor * size.value());
	setValue("V2_inner",	factor * size.value());
	setValue("V1_outer",	factor * size.value());
	setValue("V2_outer",	factor * size.value());
}



// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void ConeField::setField() noexcept(ndebug)
{
	if (tag() == 0)
		error(FUNC_INFO, "field doesn't exist");

	interface::GmshSetBGMesh {}(this);

	set_ = true;
}


String ConeField::type() const noexcept
{
	return type_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
