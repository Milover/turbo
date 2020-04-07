/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::PositiveValue

Description
	Class PositiveValue.
	Base class template for registry object requiring positive values.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_POSITIVE_VALUE_H
#define INPUT_POSITIVE_VALUE_H

#include <type_traits>
#include <utility>

#include "Error.h"
#include "RegistryObject.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class PositiveValue Definition
\*---------------------------------------------------------------------------*/

template<typename T>
class PositiveValue
:
	public RegistryObject<T>
{
protected:

	static_assert(std::is_arithmetic_v<T>);

	using PVBase = typename PositiveValue<T>;


	// Constructors

		//- Default constructor
		explicit PositiveValue(T&& t);


	// Member functions

		//- Check input
		virtual void check() const override;


public:

	// Constructors

		//- Copy constructor
		PositiveValue(const PositiveValue&) = default;

		//- Move constructor
		PositiveValue(PositiveValue&&) = default;


	//- Destructor
	virtual ~PositiveValue() = default;


	// Member operators

		//- Copy assignment operator
		PositiveValue& operator=(const PositiveValue&) = default;

		//- Move assignment operator
		PositiveValue& operator=(PositiveValue&&) = default;

};


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

template<typename T>
PositiveValue<T>::PositiveValue(T&& t)
:
	RegBase {std::forward<T>(t)}
{
	this->check();
}


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<typename T>
void PositiveValue<T>::check() const
{
	if constexpr (std::is_integral_v<T>)
		if (this->value_ < 0)
			THROW_ARGUMENT_ERROR("value < 0");
	else
		if
		(
			!isGreaterOrEqual(this->value_, 0.0)
		)
			THROW_ARGUMENT_ERROR("value < 0");
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //