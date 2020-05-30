/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::InletRefPoint

Description
	Class InletRefPoint.

	Pressure reference point, positioned at inlet center.

SourceFiles
	InletRefPoint.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_INLET_REF_POINT_H
#define INPUT_INLET_REF_POINT_H

#include "Chord.h"
#include "Error.h"
#include "RelMeshSize.h"
#include "RegistryObject.h"
#include "SectionExtensionFactor.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class InletRefPoint Declaration
\*---------------------------------------------------------------------------*/

class InletRefPoint final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const String name {"InletRefPoint"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		explicit InletRefPoint(const Vector& v) noexcept(ndebug);

		//- Compute and construct
		InletRefPoint
		(
			const Chord& c,
			const RelMeshSize& rms,
			const SectionExtensionFactor& sef,
			const Vector& lePoint
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
