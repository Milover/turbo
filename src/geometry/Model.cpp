/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <algorithm>
#include <utility>

#include <gmsh.h>

#include "Model.h"

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

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

std::size_t Model::activeId() noexcept
{
	return Model::activeId_;
}


bool Model::activate() const noexcept
{
	return activate(id_);
}


bool Model::activate(const std::size_t id) noexcept
{
	if
	(
	 	id != 0
	 && Model::activeId_ != id
	 && std::find
	 	(
			Model::log_.begin(),
			Model::log_.end(),
			id
		) != Model::log_.end()
	)
	{
		Model::activeId_ = id;
		gmsh::model::setCurrent(std::to_string(id));

		return true;
	}
	else if (Model::activeId_ == id)
		return true;

	return false;
}


std::size_t Model::id() const noexcept
{
	return id_;
}


String Model::name() const noexcept
{
	return std::to_string(id_);
}


void Model::purge() const noexcept
{
	if (id_ != 0)
	{
		activate();

		gmsh::model::remove();
		gmsh::model::add(name());
		gmsh::model::setCurrent(name());
	}
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
