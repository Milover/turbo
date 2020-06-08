/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::DistributedValue

Description
	Class DistributedValue.

	Base class template for registry objects defined via a polyline i.e.
	radial distributions of regular registry objects.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_DISTRIBUTED_VALUE_H
#define INPUT_DISTRIBUTED_VALUE_H

#include <type_traits>
#include <utility>

#include "Error.h"
#include "General.h"
#include "Polyline.h"
#include "RegistryObject.h"
#include "RegistryObjectBase.h"
#include "RelRadius.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class DistributedValue Definition
\*---------------------------------------------------------------------------*/

template<typename T>
class DistributedValue
:
	public RegistryObject<math::Polyline<typename T::type>>
{
protected:

	static_assert
	(
		std::is_base_of_v<RegistryObjectBase, T>
	);

	using RegBase = RegistryObject<math::Polyline<typename T::type>>;
	using DVBase = DistributedValue<T>;


	// Constructors

		//- Construct from values
		template
		<
			typename... U,
			typename = std::enable_if_t
			<
				(std::is_same_v<typename T::type, removeCVRef_t<U>> && ...)
			>
		>
		DistributedValue(U&&... u) noexcept(ndebug);

		//- Construct from a Polyline
		template
		<
			typename U,
			typename = std::enable_if_t
			<
				std::is_same_v<typename RegBase::type, removeCVRef_t<U>>
			>
		>
		explicit DistributedValue(U&& u) noexcept(ndebug);


	// Member functions

		//- Check input
		virtual void check() const noexcept(ndebug) override;


public:

	using type = math::Polyline<typename T::type>;
	using distributed_type = T;


	// Constructors

		//- Copy constructor
		DistributedValue(const DistributedValue&) = default;

		//- Move constructor
		DistributedValue(DistributedValue&&) = default;


	//- Destructor
	virtual ~DistributedValue() = default;

	// Member functions

		//- Get interpolated value at rel. radius
		T valueAt(const RelRadius& r_rel) const;


	// Member operators

		//- Copy assignment operator
		DistributedValue& operator=(const DistributedValue&) = default;

		//- Move assignment operator
		DistributedValue& operator=(DistributedValue&&) = default;

};


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

template<typename T>
template<typename... U, typename>
DistributedValue<T>::DistributedValue(U&&... u) noexcept(ndebug)
:
	RegBase
	{
		typename RegBase::type {std::forward<U>(u)...}
	}
{
	this->check();
}


template<typename T>
template<typename U, typename>
DistributedValue<T>::DistributedValue(U&& u) noexcept(ndebug)
:
	RegBase {std::forward<U>(u)}
{
	this->check();
}


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<typename T>
void DistributedValue<T>::check() const noexcept(ndebug)
{
	if (this->value().pointsCRef().empty())
		error(FUNC_INFO, "polyline empty");
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T>
T DistributedValue<T>::valueAt(const RelRadius& r_rel) const
{
	return T
	{
		this->value()(r_rel.value())
	};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
