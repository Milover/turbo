/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::BLNumberOfLayers

Description
	Class BLNumberOfLayers.

	Defaults to 5.

SourceFiles
	BLNumberOfLayers.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_BL_NUMBER_OF_LAYERS_H
#define INPUT_BL_NUMBER_OF_LAYERS_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class BLNumberOfLayers Declaration
\*---------------------------------------------------------------------------*/

class BLNumberOfLayers final
:
	public PositiveValue<Integer>
{
public:

	// Public static data

		inline static const String name {"BLNumberOfLayers"};


	// Constructors

		//- Default constructor
		BLNumberOfLayers() noexcept;

		//- Construct from a Integer,
		//  no aditional checking required
		explicit BLNumberOfLayers(const Integer i);


	// Member functions

		//- Get object name
		String getName() const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
