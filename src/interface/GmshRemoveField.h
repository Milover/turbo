/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshRemoveField

Description
	GmshRemoveField class

SourceFiles
	GmshRemoveField.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_REMOVE_FIELD_H
#define INTERFACE_GMSH_REMOVE_FIELD_H

#include <type_traits>

#include "General.h"
#include "SizeFieldBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshRemoveField Definition
\*---------------------------------------------------------------------------*/

class GmshRemoveField
{
private:

	//- Execute removal
	void execute(const std::size_t tag) const noexcept;


public:

	//- Remove geometry
	template
	<
		typename Field,
		typename = std::enable_if_t
		<
			std::is_base_of_v<mesh::SizeFieldBase, Field>
		>
	>
	void operator()(const Field* f) const noexcept;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename Field, typename>
void GmshRemoveField::operator()(const Field* f) const noexcept
{
	execute(f->tag());
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
