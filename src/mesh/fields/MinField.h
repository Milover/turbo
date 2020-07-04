/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::MinField

Description
	MinField class.

SourceFiles
	MinField.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_FIELDS_MIN_FIELD_H
#define MESH_FIELDS_MIN_FIELD_H

#include <cassert>
#include <type_traits>

#include "Error.h"
#include "General.h"
#include "GmshAddField.h"
#include "SizeField.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

/*---------------------------------------------------------------------------*\
						Class MinField Declaration
\*---------------------------------------------------------------------------*/

class MinField
:
	public SizeField
{
private:

	// Private data

		inline static const String type_ {"Min"};


public:

	// Constructors

		//- Construct from Fields
		template
		<
			typename... Fields,
			typename = std::enable_if_t
			<
				(std::is_base_of_v<SizeField, Fields> && ...)
			>
		>
		MinField(const Fields&... fs);

		//- Construct from a vector of Fields
		MinField(const Sptrvector<SizeField>& fields);

		//- Construct from a vector of Fields
		MinField(const Uptrvector<SizeField>& fields);


	// Member functions

		//- Set field
		void setField() noexcept(ndebug) override;

		//- Get type
		[[nodiscard]] String type() const noexcept override;

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename... Fields, typename>
MinField::MinField(const Fields&... fs)
{
	auto returnTag {interface::GmshAddField {}(this)};
	assert(returnTag == tag());

	setValue
	(
		"FieldsList",
		static_cast<Float>(fs.tag())...
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
