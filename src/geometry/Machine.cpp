/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <string>
#include <utility>
#include <memory>

#include "gmsh.h"

#include "Machine.h"
#include "Error.h"
#include "InputObjectBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Machine::buildInputMap() noexcept
{
	store("deltaP",			NAN);	// [Pa]
	store("density",		NAN);	// [kg m-3]
	store("rpm",			NAN);	// [min-1]
	store("volumeFlowRate",	NAN);	// [m3 s-1]
}


void Machine::check() const
{
	for (const auto& [key, value] : this->inputMap_)
		if (isLessOrEqual(value, 0.0))
			THROW_RUNTIME_ERROR("value of keyword '" + key + "' <= 0");
}


void Machine::computeAndStore() noexcept
{}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Machine::Machine(const Stringmap<>& input)
{
	buildInputMap();
	parse(input);
	check();

	gmsh::model::add(name_);

	rotor_.reset					// <- should be a loop at some point
	(
		new BladeRow {input, *this}
	);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Machine::build()
{
	rotor_->build();
}


const BladeRow* Machine::getRotor() const noexcept
{
	return &(*rotor_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
