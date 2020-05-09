/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "SizeFieldBase.h"

#include "General.h"
#include "GmshRemoveField.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

SizeFieldBase::SizeFieldBase() noexcept
:
	tag_ {++SizeFieldBase::count_}
{}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

SizeFieldBase::SizeFieldBase(SizeFieldBase&& sf) noexcept
:
	tag_ {sf.tag_}
{
	sf.tag_ = 0;
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

SizeFieldBase::~SizeFieldBase() noexcept
{
	if (tag_ != 0)
		interface::GmshRemoveField {}(this);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

std::size_t SizeFieldBase::count() noexcept
{
	return SizeFieldBase::count_;
}


bool SizeFieldBase::set() const noexcept
{
	return set_;
}


std::size_t SizeFieldBase::tag() const noexcept
{
	return tag_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// ************************************************************************* //
