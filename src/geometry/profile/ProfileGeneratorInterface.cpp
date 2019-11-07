/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <memory>
#include <stdexcept>

#include "NacaProfileGenerator.h"
#include "Point.h"
#include "ProfileGeneratorInterface.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void ProfileGeneratorInterface::createInterfaceObject(const Stringmap& input)
{
	auto buildFrom {input.find("buildFrom")};

	if (buildFrom == input.end())
	{
		throw std::runtime_error
		(
			"turbo::geometry::ProfileGeneratorInterface::"
			"createInterfaceObject(const turbo::Stringmap&): "
			"Keyword \"buildFrom\" undefined"
		);
	}
	else if (buildFrom->second == "naca")
	{
		interfaceObject_ = std::make_unique<NacaProfileGenerator>(input);
	}
	else
	{
		throw std::invalid_argument
		(
			"turbo::geometry::ProfileGeneratorInterface::"
			"createInterfaceObject(const turbo::Stringmap&): "
			"Unknown value of keyword \"buildFrom\""
		);
	}
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ProfileGeneratorInterface::ProfileGeneratorInterface(const Stringmap& input)
{
	createInterfaceObject(input);

	interfaceObject_->generate();
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

ProfileGeneratorInterface::~ProfileGeneratorInterface()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

int ProfileGeneratorInterface::getSize() const noexcept
{
	return interfaceObject_->getSize();
}


bool ProfileGeneratorInterface::isEmpty() const noexcept
{
	return interfaceObject_->isEmpty();
}


Point ProfileGeneratorInterface::getUpperPointAt(const int pos) const
{
	return Point
	{
		interfaceObject_->getUpperAt(pos).first,
		interfaceObject_->getUpperAt(pos).second
	};
}


Point ProfileGeneratorInterface::getLowerPointAt(const int pos) const
{
	return Point
	{
		interfaceObject_->getLowerAt(pos).first,
		interfaceObject_->getLowerAt(pos).second
	};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
