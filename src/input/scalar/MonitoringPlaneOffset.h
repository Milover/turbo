/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::MonitoringPlaneOffset

Description
	Class MonitoringPlaneOffset.

	Offset of monitoring plane (foam postprocessing) from LE/TE point in the
	streamwise direction (x-axis), given as percent of chord.

	Defaults to 0.05;

Sourcefiles
	MonitoringPlaneOffset.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_MONITORING_PLANE_OFFSET_H
#define INPUT_MONITORING_PLANE_OFFSET_H

#include "General.h"
#include "RegistryObject.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class MonitoringPlaneOffset Declaration
\*---------------------------------------------------------------------------*/

class MonitoringPlaneOffset final
:
	public RegistryObject<Float>
{
public:

	// Public static data

		inline static const String name {"MonitoringPlaneOffset"};


	// Constructors

		//- Default constructor
		MonitoringPlaneOffset() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit MonitoringPlaneOffset(const Float f);


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
