/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::ManipulatorBase

Description
	Abstract base class template for manipulation of geometry.

\*---------------------------------------------------------------------------*/

#ifndef MANIPULATOR_BASE_H
#define MANIPULATOR_BASE_H

#include "CascadeComponentBase.h"
#include "Shape.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class ManipulatorBase Declaration
\*---------------------------------------------------------------------------*/

template<typename... T>
class ManipulatorBase
{
protected:

	// Constructors
		
		//- Default constructor
		ManipulatorBase() = default;


	// Member functions

		//- Execute geometry manipulation
		virtual void executeManipulation
		(
			const Vectorpair<int>& dimTags
		) const = 0;


public:

	// Constructors

		//- Disallow copy construction
		ManipulatorBase(const ManipulatorBase&) = delete;


	//- Destructor
	virtual ~ManipulatorBase() = default;


	// Member functions

		//- Set manipulation parameter
		virtual void setParameters(const T&... t) noexcept = 0;

		//- Check if manipulation parameters are set
		virtual bool isSet() const noexcept = 0;

		//- Manipulate primitive geometry
		inline void manipulate(const Shape& shape) const
		{
			executeManipulation
			(
				Vectorpair<int> {shape.getDimTag()}
			);
		}

		//- Manipulate cascade geometry
		inline void manipulate
		(
			const CascadeComponentBase& component
		) const
		{
			executeManipulation(component.getDimTags());
		}


	// Member operators

		//- Disallow assignment
		ManipulatorBase& operator=(const ManipulatorBase&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
