/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::Machine

Description
	Machine class

SourceFiles
	Machine.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_MACHINE_H
#define DESIGN_MACHINE_H

#include "BladeRow.h"
#include "Registry.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
						Class Machine Declaration
\*---------------------------------------------------------------------------*/

class Machine
{
private:

	// Private data

		String name_ {"machine"};

		Registry& data_;
		Uptr<BladeRow> rotor_;				// TODO: implement multiples at some point


protected:

	// Member functions

		//- Build input map
		void buildInputMap() noexcept override;

		//- Check values
		void check() const override;

		//- Empty overload
		void computeAndStore() noexcept;


public:

	// Constructors

		//- Default constructor
		Machine(const Stringmap<>& input);

		//- Disallow copy constructor
		Machine(const Machine&) = delete;

		//- Move constructor
		Machine(Machine&&) = default;


	//- Destructor
	virtual ~Machine() = default;


	// Member functions

		//- Build geometry
		void build();

		//- Write geometry to file
		// void write() const noexcept;		// <- implement later


	// Member operators

		//- Dissalow copy assignment operator
		Machine& operator=(const Machine&) = delete;

		//- Move assignment operator
		Machine& operator=(Machine&&) = default;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
