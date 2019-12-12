/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Machine

Description
	Machine class

SourceFiles
	Machine.cpp

\*---------------------------------------------------------------------------*/

#ifndef MACHINE_H
#define MACHINE_H

#include <memory>
#include <string>

#include "BladeRow.h"
#include "ComponentBase.h"
#include "InputObjectBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Machine Declaration
\*---------------------------------------------------------------------------*/

class Machine final
:
	public ComponentBase
{
private:

	// Private data

		std::unique_ptr<BladeRow> rotor_;	// <- implement multiples later
		std::string name_ {"machine"};


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

		//- Move constructor
		Machine(Machine&&) = default;


	//- Destructor
	virtual ~Machine() = default;


	// Member functions

		// General

		//- Build geometry
		void build();

		//- Write geometry to file
		// void write() const noexcept;		// <- implement later

		//- Get const pointer to rotor
		const BladeRow* getRotor() const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
