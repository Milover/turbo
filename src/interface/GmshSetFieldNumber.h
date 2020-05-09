/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshSetFieldNumber

Description
	GmshSetFieldNumber class

SourceFiles
	GmshSetFieldNumber.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_SET_FIELD_NUMBER_H
#define INTERFACE_GMSH_SET_FIELD_NUMBER_H

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
					Class GmshSetFieldNumber Declaration
\*---------------------------------------------------------------------------*/

class GmshSetFieldNumber
{
private:

	//- Execute
	void execute
	(
		const std::size_t tag,
		const String& variable,
		const Float value
	) const noexcept;


public:

	//- Set a mesh size field number value
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
		const Float value
	) const noexcept;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename Field, typename>
void GmshSetFieldNumber::operator()
(
	const Field* f,
	const String& variable,
	const Float value
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
