/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>
#include <limits>

#include "BoxField.h"

#include "Error.h"
#include "General.h"
#include "GmshAddField.h"
#include "GmshSetBGMesh.h"
#include "Registry.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

BoxField::BoxField(const input::Registry& reg)
{
	auto returnTag {interface::GmshAddField {}(this)};

	assert(returnTag == tag());

	input::MeshCellSize size
	{
		reg.cref<input::Chord>(),
		reg.cref<input::RelMeshSize>()
	};

	auto min	// :)
	{
		static_cast<Float>(std::numeric_limits<Integer>::min())
	};
	auto max	// :)
	{
		static_cast<Float>(std::numeric_limits<Integer>::max())
	};

	setValue("VIn",		size.value());
	setValue("XMin",	min);
	setValue("YMin",	min);
	setValue("ZMin",	min);
	setValue("XMax",	max);
	setValue("YMax",	max);
	setValue("ZMax",	max);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void BoxField::setField() noexcept(ndebug)
{
	if (tag() == 0)
		error(FUNC_INFO, "field doesn't exist");

	interface::GmshSetBGMesh {}(this);

	set_ = true;
}


String BoxField::type() const noexcept
{
	return type_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
