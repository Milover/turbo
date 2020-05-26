/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TEMonitoringPlane

Description
	Class TEMonitoringPlane.

	Point used to define the monitoring plane (foam postprocessing) at
	the leading edge.

SourceFiles
	TEMonitoringPlane.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TE_MONITORING_PLANE_H
#define INPUT_TE_MONITORING_PLANE_H

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
					Class TEMonitoringPlane Declaration
\*---------------------------------------------------------------------------*/

class TEMonitoringPlane final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const String name {"TEMonitoringPlane"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		explicit TEMonitoringPlane(const Vector& v) noexcept(ndebug);

		//- Compute and construct
		TEMonitoringPlane
		(
			const Vector& tePoint,
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
