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

#include <type_traits>

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


public:

	// Constructors

		//- Disallow copy construction
		ManipulatorBase(const ManipulatorBase&) = delete;


	//- Destructor
	virtual ~ManipulatorBase() = default;


	// Member functions

		//- Manipulate geometry
		virtual void manipulate(const Vectorpair<int>& dimTags) const = 0;

		//- Check if manipulation parameters are set
		virtual bool isSet() const noexcept = 0;

		//- Set manipulation parameter
		virtual void setParameters(const T&... t) noexcept = 0;


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
