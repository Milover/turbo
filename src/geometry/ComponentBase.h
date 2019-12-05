/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::ComponentBase

Description
	Abstract base class template for generic turbomachinery components.

SourceFiles
	ComponentBase.cpp

\*---------------------------------------------------------------------------*/

#ifndef COMPONENT_BASE_H
#define COMPONENT_BASE_H

#include <memory>
#include <string>

#include "InputObjectBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class ComponentBase Declaration
\*---------------------------------------------------------------------------*/

class ComponentBase
:
	public InputObjectBase<double>
{
protected:

	// Protected data


		const ComponentBase* owner_ {nullptr};


	// Constructors

		//- Default constructor
		ComponentBase() = default;


	// Member functions

		//- Check input
		virtual void check() const = 0;

		//- Compute and store values to input map
		virtual void computeAndStore() = 0;

		//- Convert value
		double convert(const std::string& value) const final;


public:

	// Constructors

		//- Move constructor
		ComponentBase(ComponentBase&&) = delete;


	//- Destructor
	virtual ~ComponentBase() = default;


	// Member functions

		//- Build geometry
		virtual void build() = 0;

		//- Ask owner for value
		double get(const std::string& key) const final;

		//- Check if value is initialized
		bool hasValue(const std::string& key) const noexcept final;

		//- Get dimTags
		virtual Vectorpair<int> getDimTags() const noexcept = 0;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
