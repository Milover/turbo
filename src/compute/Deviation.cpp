/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <memory>
#include <string>

#include "CarterDeviation.h"
#include "ComponentBase.h"
#include "Deviation.h"
#include "Error.h"
#include "McKenzieDeviation.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Deviation::Deviation(const Stringmap<>& input)
{
	auto search {input.find("deviation")};

	if (search == input.end())
		return;

	std::string type {search->second};

	if (type == "carter")
		method_.reset
		(
			new CarterDeviation {}
		);
	else if (type == "mckenzie")
		method_.reset
		(
			new McKenzieDeviation {}
		);
	else
		THROW_RUNTIME_ERROR("unknown value '" + type + "' for keyword 'deviation'");
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

double Deviation::compute(const ComponentBase& component) const
{
	if
	(
		!static_cast<bool>(method_)
	)
		return 0.0;

	return method_->compute(component);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
