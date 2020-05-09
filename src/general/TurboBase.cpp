/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <filesystem>

#include "TurboBase.h"

#include "General.h"
#include "Model.h"
#include "Registry.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

TurboBase::TurboBase(const Path& file)
:
	ownsData_ {true},
	data_ {new input::Registry {}},		// we own and manage
	model_ {new geometry::Model {}}
{
	if (std::filesystem::is_directory(file))
		file_ = file / "";
}


TurboBase::TurboBase
(
	const input::Registry& reg,
	const Path& file
)
:
	ownsData_ {false},
	data_					// we don't own or manage but have access
	{
		&const_cast<input::Registry&>(reg).create()
	},
	model_ {new geometry::Model {}}
{
	if (std::filesystem::is_directory(file))
		file_ = file / "";
}


// * * * * * * * * * * * * Protected Member Functions* * * * * * * * * * * * //

void TurboBase::adjustFilename
(
	const String& prefix,
	const String& extension
)
{
	addFilenamePrefix(file_, prefix);
	file_.replace_extension(extension);
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

TurboBase::~TurboBase() noexcept
{
	if (ownsData_)
		delete data_;
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Path TurboBase::file() const
{
	return file_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// ************************************************************************* //
