/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include "AutomaticMeshSizeField.h"

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

AutomaticMeshSizeField::AutomaticMeshSizeField(const input::Registry& reg)
{
	auto returnTag {interface::GmshAddField {}(this)};

	assert(returnTag == tag());

	// set characteristics
	input::BLGrowthRate rate
	{
		reg.cref<input::BLGrowthRate>()
	};
	input::MeshCellSize size
	{
		reg.cref<input::MeshCellSize>()
	};

	setValue("hBulk",				size.value());
	setValue("gradientMax",			rate.value());
	setValue("NRefine",				5.0);		// default
	setValue("nPointsPerCircle",	55.0);		// default
	setValue("nPointsPerGap",		5.0);		// default
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void AutomaticMeshSizeField::setField() noexcept(ndebug)
{
	if (tag() == 0)
		error(FUNC_INFO, "field doesn't exist");

	interface::GmshSetBGMesh {}(this);

	set_ = true;
}


String AutomaticMeshSizeField::type() const noexcept
{
	return type_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
