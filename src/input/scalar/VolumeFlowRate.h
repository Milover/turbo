/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::VolumeFlowRate

Description
	Class VolumeFlowRate.

SourceFiles
	VolumeFlowRate.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_VOLUME_FLOW_RATE_H
#define INPUT_VOLUME_FLOW_RATE_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class VolumeFlowRate Declaration
\*---------------------------------------------------------------------------*/

class VolumeFlowRate final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"VolumeFlowRate"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit VolumeFlowRate(const Float f);


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
