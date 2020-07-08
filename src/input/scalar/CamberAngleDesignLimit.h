/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::CamberAngleDesignLimit

Description
	Class CamberAngleDesignLimit.

	Sets the limit (limit * analytical camber angle) to which the camber angle
	can be increased during the design procedure. 

	Defaults to 5.0.

SourceFiles
	CamberAngleDesignLimit.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_CAMBER_ANGLE_DESIGN_LIMIT_H
#define INPUT_CAMBER_ANGLE_DESIGN_LIMIT_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class CamberAngleDesignLimit Declaration
\*---------------------------------------------------------------------------*/

class CamberAngleDesignLimit final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"CamberAngleDesignLimit"};


	// Constructors

		//- Default constructor
		CamberAngleDesignLimit() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit CamberAngleDesignLimit(const Float f);


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
