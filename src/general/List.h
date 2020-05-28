/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::List

Description
	List class.

\*---------------------------------------------------------------------------*/

#ifndef LIST_H
#define LIST_H

#include <type_traits>
#include <istream>
#include <ostream>

#include "Error.h"
#include "General.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

/*---------------------------------------------------------------------------*\
						Class List Definition
\*---------------------------------------------------------------------------*/

template<typename T>
class List
{
private:

	using Type = std::vector<T>;

	// Private data

		Type data_;

public:

	// Constructors

		//- Default constructor
		List() = default;

		//- Construct from data
		template
		<
			typename... U,
			typename = std::enable_if_t
			<
				(std::is_same_v<T, removeCVRef_t<U>> && ...)
			>
		>
		List(U&&... u) noexcept;

		//- Construct from data
		template
		<
			typename U,
			typename = std::enable_if_t<std::is_same_v<Type, removeCVRef_t<U>>>
		>
		List(Type&& data) noexcept;

		//- Copy constructor
		List(const List&) = default;

		//- Move constructor
		List(List&&) = default;


	// Destructor
	~List() = default;


	// Member functions

		//- Get data
		const Type& dataCRef() const noexcept;

		//- Get data
		Type& dataRef() noexcept;


	// Member operators

		//- Copy assignment operator
		List& operator=(const List&) = default;

		//- Move assignment operator
		List& operator=(List&&) = default;

};


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //



// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
