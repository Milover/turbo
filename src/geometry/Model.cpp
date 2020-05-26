/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <algorithm>
#include <utility>

#include <gmsh.h>

#include "General.h"
#include "Model.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

bool Model::activate(const std::size_t id) const noexcept
{
	if
	(
	 	id != 0
	 && activeId_ != id
	 && std::find(log_.begin(), log_.end(), id) != log_.end()
	)
	{
		activeId_ = id;
		gmsh::model::setCurrent(std::to_string(id));

		return true;
	}

	return false;
}


void Model::remove() const noexcept
{
	auto previous {Model::activeId_};

	// needs to be the current (active) model to be removed
	activate();
	gmsh::model::remove();
	log_.remove(id_);

	// reactivate the previous model if possible,
	// unless we're the only model
	if (previous != id_)
		activate(previous);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Model::Model() noexcept
:
	id_ {++count_}
{
	log_.emplace_back(id_);
	activeId_ = id_;

	gmsh::model::add(name());
}


Model::Model(Model&& m) noexcept
:
	id_ {std::move(m.id_)}
{
	m.id_ = 0;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Model::~Model() noexcept
{
	if (id_ != 0)
		remove();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Model::activate() const noexcept
{
	return activate(id_);
}


std::size_t Model::id() const noexcept
{
	return id_;
}


String Model::name() const noexcept
{
	return std::to_string(id_);
}


void Model::write
(
	const String& extension,
	const String& prefix,
	const String& suffix
) const noexcept
{
	if (id_ != 0)
	{
		String filename {name()};

		if (!prefix.empty())
			filename = prefix + "_" + filename;

		if (!suffix.empty())
			filename = filename + "_" + suffix;

		filename = filename + "." + extension;

		activate();
		gmsh::write(filename);
	}
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

Model::operator bool() const noexcept
{
	if (id_ != 0)
		return true;

	return false;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
