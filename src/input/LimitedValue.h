/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::LimitedValue

Description
	Class LimitedValue.
	Base class template for registry object requiring the value to be
	constrained within (inclusive) limits i.e. within the set [Low, High].

\*---------------------------------------------------------------------------*/

#ifndef INPUT_LIMITED_VALUE_H
#define INPUT_LIMITED_VALUE_H

#include <type_traits>
#include <utility>

#include "Error.h"
#include "General.h"
#include "RegistryObject.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class LimitedValue Definition
\*---------------------------------------------------------------------------*/

template<typename T, Integer Low, Integer High>
class LimitedValue
:
	public RegistryObject<T>
{
protected:

	static_assert(std::is_arithmetic_v<T>);
	static_assert(Low < High);

	using RegBase = RegistryObject<T>;
	using LVBase = LimitedValue<T, Low, High>;


	// Constructors

		//- Construct from input
		template
		<
			typename U,
			std::enable_if_t<std::is_same_v<T, removeCVRef_t<U>>, int> = 0
		>
		explicit LimitedValue(U&& u);


	// Member functions

		//- Check input
		virtual void check() const override;


public:

	using type = T;


	// Constructors

		//- Copy constructor
		LimitedValue(const LimitedValue&) = default;

		//- Move constructor
		LimitedValue(LimitedValue&&) = default;


	//- Destructor
	virtual ~LimitedValue() = default;


	// Member operators

		//- Copy assignment operator
		LimitedValue& operator=(const LimitedValue&) = default;

		//- Move assignment operator
		LimitedValue& operator=(LimitedValue&&) = default;

};


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

template<typename T, Integer Low, Integer High>
template
<
	typename U,
	std::enable_if_t<std::is_same_v<T, removeCVRef_t<U>>, int>
>
LimitedValue<T, Low, High>::LimitedValue(U&& u)
:
	RegBase {std::forward<U>(u)}
{
	this->check();
}


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<typename T, Integer Low, Integer High>
void LimitedValue<T, Low, High>::check() const
{
	if constexpr (std::is_integral_v<T>)
	{
		if
		(
			this->value_ < Low || this->value_ > High
		)
			THROW_ARGUMENT_ERROR
			(
				"value not in range [" + std::to_string(Low)
			  + ", " + std::to_string(High) + "]"
			);
	}
	else
	{
		if
		(
			!isInRange
			(
				this->value_,
				static_cast<Float>(Low),
				static_cast<Float>(High)
			)
		)
			THROW_ARGUMENT_ERROR
			(
				"value not in range [" + std::to_string(Low)
			  + ", " + std::to_string(High) + "]"
			);
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
