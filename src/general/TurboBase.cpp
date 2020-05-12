/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <filesystem>
#include <ostream>

#include "TurboBase.h"

#include "Error.h"
#include "General.h"
#include "Model.h"
#include "Registry.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * Private Functions * * * * * * * * * * * * * * //

void TurboBase::setFile(const Path& file)
{
	if (std::filesystem::is_directory(file))
		file_ = file / "";
	
	if (!file_.has_filename())
		file_.replace_filename(model_->name());
}


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

TurboBase::TurboBase(const Path& file)
:
	ownsData_ {true},
	data_ {new input::Registry {}},		// we own and manage
	model_ {new geometry::Model {}}
{
	setFile(file);
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
	setFile(file);
}


// * * * * * * * * * * * * Protected Member Functions* * * * * * * * * * * * //

void TurboBase::setFile
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


void TurboBase::changeDirectory(const Path& directory)
{
	Path newDir {directory};

	if (directory.is_relative())
		newDir = file_.parent_path() / directory;

	if (!std::filesystem::is_directory(newDir))
		error(FUNC_INFO, "directory: ", newDir, " doesn't exist");

	file_ = newDir / file_.filename();
}


void TurboBase::changeDirectoryParent()
{
	file_ = file_.parent_path().parent_path() / file_.filename();
}


void TurboBase::printAll
(
	std::ostream& os,
	const String::size_type width,
	const String& delimiter,
	const String& terminator
) const
{
	data_->printAll(os, width, delimiter, terminator);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// ************************************************************************* //
