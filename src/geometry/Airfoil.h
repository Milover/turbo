/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Airfoil

Description
	Class Airfoil

SourceFiles
	Airfoil.cpp

\*---------------------------------------------------------------------------*/

#ifndef AIRFOIL_H
#define AIRFOIL_H

#include "CascadeComponentBase.h"
#include "Point.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Airfoil Declaration
\*---------------------------------------------------------------------------*/

class Airfoil final
:
	public CascadeComponentBase
{
private:
	
	// Private data

		bool evolved;

protected:

	// Member functions

		//- Build geometry
		void generatePoints(const Stringmap& input) override;

		//- Get vector of dimTags of underlying geometry
		 Vectorpair<int> getDimTags() const noexcept override;


public:
	
	// Constructors

		//- Construct from input map
		Airfoil(const Stringmap& input);

		//- Copy constructor
		Airfoil(const Airfoil&);


	//- Destructor
	~Airfoil();


	// Member functions

		//- Build geometry
		void build();

		//- Create cylindrical section and evolve,
		//  cylinder radius is determined from current
		//  geometric center
		void evolveSection();							// not implemented

		//- Return evolved state
		bool isEvolved() const noexcept;


	// Member operators
	
		//- Disallow assignment
		Airfoil& operator=(const Airfoil&) = delete;


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
