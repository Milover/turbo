/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::SizeField

Description
	Abstract base class for size field classes.

SourceFiles
	SizeField.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_FIELDS_SIZE_FIELD_H
#define MESH_FIELDS_SIZE_FIELD_H

#include <type_traits>
#include <utility>

#include "General.h"
#include "GmshSetFieldNumber.h"
#include "GmshSetFieldNumbers.h"
#include "GmshSetFieldString.h"
#include "SizeFieldBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

/*---------------------------------------------------------------------------*\
					Class SizeField Declaration
\*---------------------------------------------------------------------------*/

class SizeField
:
	public SizeFieldBase
{
private:

	template<typename T>
	inline static constexpr bool isValid_v =
		std::is_same_v<Float, removeCVRef_t<T>>
	 || std::is_same_v<String, removeCVRef_t<T>>;


protected:

	// Constructors

		//- Default constructor
		SizeField() = default;


	// Member functions

		//- Set number variable
		void setValue
		(
			const String& variable,
			const Floatvector& values
		) const noexcept;

		//- Set number variable
		template
		<
			typename... Values,
			typename = std::enable_if_t<(isValid_v<Values> && ...)>
		>
		void setValue
		(
			const String& variable,
			Values&&... vs
		) const noexcept;


public:

	// Constructors

		//- Disallow copy constructor
		SizeField(const SizeField&) = delete;

		//- Move constructor
		SizeField(SizeField&&) = default;


	//- Destructor
	virtual ~SizeField() = default;


	// Member operators

		//- Disallow copy assignment operator
		SizeField& operator=(const SizeField&) = delete;

		//- Disallow move assignment operator
		SizeField& operator=(SizeField&&) = delete;

};


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<typename... Values, typename>
void SizeField::setValue
(
	const String& variable,
	Values&&... vs
) const noexcept
{
	constexpr auto size {sizeof...(vs)};

	static_assert(size > 0);

	if constexpr (size == 1)
	{
		if constexpr
		(
			(std::is_same_v<Float, removeCVRef_t<Values>> && ...)
		)
		{
			interface::GmshSetFieldNumber {}
			(
				this,
				variable,
				std::forward<Values>(vs)...
			);
		}
		else
		{
			interface::GmshSetFieldString {}
			(
				this,
				variable,
				std::forward<Values>(vs)...
			);
		}
	}
	else
	{
		static_assert
		(
			(std::is_same_v<Float, removeCVRef_t<Values>> && ...)
		);

		Floatvector vals;
		vals.reserve(size);

		(vals.emplace_back(std::forward<Values>(vs)), ...);

		interface::GmshSetFieldNumbers {}(this, variable, vals);
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
