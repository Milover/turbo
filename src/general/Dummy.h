/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::Dummy

Description
	Dummy class.

	A dummy functor, taking anything and doing nothing with it.

\*---------------------------------------------------------------------------*/

#ifndef DUMMY_H
#define DUMMY_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

/*---------------------------------------------------------------------------*\
							Class Dummy Definition
\*---------------------------------------------------------------------------*/

struct Dummy
{
	//- Take anything and do nothing
	template<typename T>
	void operator()(T&&) const noexcept;

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename T>
void Dummy::operator()(T&&) const noexcept
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
