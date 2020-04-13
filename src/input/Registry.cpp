/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <memory>

#include "Registry.h"

#include "General.h"
#include "RegistryObjectBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * Private Constructors  * * * * * * * * * * * * * //

Registry::Registry(const Registry& r) noexcept
:
	owner_
	{
		&const_cast<Registry&>(r)
	},
	data_
	{
		std::make_unique<HashMap<Uptr<RegistryObjectBase>>>()
	}
{}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Registry::Registry() noexcept
:
	data_
	{
		std::make_unique<HashMap<Uptr<RegistryObjectBase>>>()
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Registry& Registry::create() noexcept
{
	if (!slaves_)
		slaves_.reset
		(
			new Ptrvector<Registry> {}
		);

	slaves_->push_back
	(
		std::unique_ptr<Registry> {new Registry {*this}}
	);
	return *(slaves_->back());
}


Registry* Registry::owner() const noexcept
{
	return this->owner_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
