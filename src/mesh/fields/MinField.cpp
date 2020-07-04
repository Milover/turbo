/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include "MinField.h"

#include "Error.h"
#include "General.h"
#include "GmshAddField.h"
#include "GmshSetBGMesh.h"
#include "SizeField.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

MinField::MinField(const Sptrvector<SizeField>& fields)
{
	auto returnTag {interface::GmshAddField {}(this)};
	assert(returnTag == tag());

	Floatvector tags;
	tags.reserve(fields.size());

	for (const auto& f : fields)
		tags.emplace_back
		(
			static_cast<Float>(f->tag())
		);

	setValue("FieldsList", tags);
}


MinField::MinField(const Uptrvector<SizeField>& fields)
{
	auto returnTag {interface::GmshAddField {}(this)};
	assert(returnTag == tag());

	Floatvector tags;
	tags.reserve(fields.size());

	for (const auto& f : fields)
		tags.emplace_back
		(
			static_cast<Float>(f->tag())
		);

	setValue("FieldsList", tags);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void MinField::setField() noexcept(ndebug)
{
	if (tag() == 0)
		error(FUNC_INFO, "field doesn't exist");

	interface::GmshSetBGMesh {}(this);

	set_ = true;
}


String MinField::type() const noexcept
{
	return type_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
