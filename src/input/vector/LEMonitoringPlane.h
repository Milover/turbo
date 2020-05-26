/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::LEMonitoringPlane

Description
	Class LEMonitoringPlane.

	Point used to define the monitoring plane (foam postprocessing) at
	the leading edge.

SourceFiles
	LEMonitoringPlane.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_LE_MONITORING_PLANE_H
#define INPUT_LE_MONITORING_PLANE_H

#include "Chord.h"
#include "Error.h"
#include "MonitoringPlaneOffset.h"
#include "RegistryObject.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class LEMonitoringPlane Declaration
\*---------------------------------------------------------------------------*/

class LEMonitoringPlane final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const String name {"LEMonitoringPlane"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		explicit LEMonitoringPlane(const Vector& v) noexcept(ndebug);

		//- Compute and construct
		LEMonitoringPlane
		(
			const Vector& lePoint,
			const Chord& c,
			const MonitoringPlaneOffset& mpo
		) noexcept(ndebug);


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
