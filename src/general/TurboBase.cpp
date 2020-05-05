/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TurboBase.h"

#include "General.h"
#include "Model.h"
#include "Registry.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

TurboBase::TurboBase()
:
	ownsData_ {true},
	data_ {new input::Registry {}},		// we own and manage
	model_ {new geometry::Model {}}
{}


TurboBase::TurboBase(const input::Registry& reg)
:
	ownsData_ {false},
	data_					// we don't own or manage but have access
	{
		&const_cast<input::Registry&>(reg).create()
	}
{}


TurboBase::TurboBase
(
	const input::Registry& reg,
	geometry::Model&& mod
)
:
	ownsData_ {false},
	data_					// we don't own or manage but have access
	{
		&const_cast<input::Registry&>(reg).create()
	},
	model_
	{
		new geometry::Model {std::move(mod)}
	}
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

TurboBase::~TurboBase() noexcept
{
	if (ownsData_)
		delete data_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
