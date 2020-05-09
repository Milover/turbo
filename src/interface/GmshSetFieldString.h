/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshSetFieldString

Description
	GmshSetFieldString class

SourceFiles
	GmshSetFieldString.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_SET_FIELD_STRING_H
#define INTERFACE_GMSH_SET_FIELD_STRING_H

#include <type_traits>

#include "Error.h"
#include "General.h"
#include "SizeFieldBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
					Class GmshSetFieldString Declaration
\*---------------------------------------------------------------------------*/

class GmshSetFieldString
{
private:

	//- Execute
	void execute
	(
		const std::size_t tag,
		const String& variable,
		const String& value
	) const noexcept;


public:

	//- Set a mesh size field string value
	template
	<
		typename Field,
		typename = std::enable_if_t
		<
			std::is_base_of_v<mesh::SizeFieldBase, Field>
		>
	>
	void operator()
	(
		const Field* f,
		const String& variable,
		const String& value
	) const noexcept;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename Field, typename>
void GmshSetFieldString::operator()
(
	const Field* f,
	const String& variable,
	const String& value
) const noexcept
{
	execute(f->tag(), variable, value);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
