/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshSetFieldNumbers

Description
	GmshSetFieldNumbers class

SourceFiles
	GmshSetFieldNumbers.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_SET_FIELD_NUMBERS_H
#define INTERFACE_GMSH_SET_FIELD_NUMBERS_H

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
					Class GmshSetFieldNumbers Declaration
\*---------------------------------------------------------------------------*/

class GmshSetFieldNumbers
{
private:

	//- Execute
	void execute
	(
		const std::size_t tag,
		const String& variable,
		const Floatvector& values
	) const noexcept;


public:

	//- Set a mesh size fields number list variable values
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
		const Floatvector& values
	) const noexcept;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename Field, typename>
void GmshSetFieldNumbers::operator()
(
	const Field* f,
	const String& variable,
	const Floatvector& values
) const noexcept
{
	execute(f->tag(), variable, values);
}



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
