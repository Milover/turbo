/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshAddField

Description
	GmshAddField class

SourceFiles
	GmshAddField.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_ADD_FIELD_H
#define INTERFACE_GMSH_ADD_FIELD_H

#include <type_traits>

#include "General.h"
#include "SizeFieldBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshAddField Definition
\*---------------------------------------------------------------------------*/

class GmshAddField
{
private:

	//- Execute
	[[maybe_unused]] std::size_t execute
	(
		const std::size_t tag,
		const String& type
	) const noexcept;


public:

	//- Create a mesh size field
	template
	<
		typename Field,
		typename = std::enable_if_t
		<
			std::is_base_of_v<mesh::SizeFieldBase, Field>
		>
	>
	[[maybe_unused]] std::size_t operator()(const Field* f) const noexcept;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename Field, typename>
std::size_t GmshAddField::operator()(const Field* f) const noexcept
{
	return execute(f->tag(), f->type());
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
