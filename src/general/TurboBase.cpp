/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>

#include "TurboBase.h"

#include "Error.h"
#include "General.h"
#include "GmshWrite.h"
#include "Model.h"
#include "Registry.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void TurboBase::handleCwd
(
	const Path& parentCwd,
	const Cwd cwd
)
{
	if (cwd == Cwd::CREATE)
	{
		setCwd(parentCwd / filename.stem());

		if (!std::filesystem::exists(cwd_))
			std::filesystem::create_directory(cwd_);
		else
		{
			restart_ = true;

			// FIXME: implement a dedicated messaging system
			//if constexpr (ndebug)
				std::cout << "restarting: " << filename.stem() << '\n';
		}
	}
	else
		setCwd(parentCwd);
}


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

TurboBase::TurboBase
(
	const Path& file,
	const Path& parentCwd,
	const std::size_t id,
	const Cwd cwd
)
:
	ownsData_ {true},
	data_ {new input::Registry {}},		// we own and manage
	model_ {new geometry::Model {}},
	id_ {id},
	filename
	{
		addFilenameSuffix(file, id)
	}
{
	handleCwd(parentCwd, cwd);
}


TurboBase::TurboBase
(
	const Path& file,
	const input::Registry& reg,
	const Path& parentCwd,
	const std::size_t id,
	const Cwd cwd
)
:
	ownsData_ {false},
	data_					// we don't own or manage but have access
	{
		&const_cast<input::Registry&>(reg).create()
	},
	model_ {new geometry::Model {}},
	id_ {id},
	filename
	{
		addFilenameSuffix(file, id)
	}
{
	handleCwd(parentCwd, cwd);
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

TurboBase::~TurboBase() noexcept
{
	if (ownsData_)
		delete data_;
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void TurboBase::activate() const
{
	model_->activate();
}


Path TurboBase::cwd() const
{
	return cwd_;
}


void TurboBase::dumpData(const Path& file) const
{
	Path outfile;

	if (file.empty())
		outfile = cwd_ / filename.stem();
	else
		outfile = file;

	if (std::filesystem::exists(file))
	{
		std::cerr << "WARNING: "
				  << "overwriting file: " << outfile << "\n";
	}

	std::ofstream ofs {outfile};
	printAll(ofs);
}


std::size_t TurboBase::id() const noexcept
{
	return id_;
}

void TurboBase::printAll
(
	std::ostream& os,
	const String::size_type width,
	const String& delimiter,
	const String& terminator,
	const Integer precision
) const
{
	data_->printAll(os, width, delimiter, terminator, precision);
}


bool TurboBase::restarted() const noexcept
{
	return restart_;
}


void TurboBase::setCwd(const Path& cwd)
{
	cwd_ = cwd;
}


void TurboBase::write() const
{
	model_->activate();

	interface::GmshWrite {}(cwd_ / filename);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// ************************************************************************* //
