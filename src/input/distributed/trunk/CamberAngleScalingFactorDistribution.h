/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::CamberAngleScalingFactorDistribution

Description
	Class CamberAngleScalingFactorDistribution.

	Defaults to 1.0.

SourceFiles
	CamberAngleScalingFactorDistribution.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_CAMBER_ANGLE_SCALING_FACTOR_DISTRIBUTION_H
#define INPUT_CAMBER_ANGLE_SCALING_FACTOR_DISTRIBUTION_H

#include <utility>

#include "Error.h"
#include "General.h"
#include "DistributedValue.h"
#include "CamberAngleScalingFactor.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
			Class CamberAngleScalingFactorDistribution Declaration
\*---------------------------------------------------------------------------*/

class [[deprecated("this will probably be removed in the future")]]
CamberAngleScalingFactorDistribution final
:
	public DistributedValue<CamberAngleScalingFactor>
{
public:

	// Public static data

		inline static const String name {"CamberAngleScalingFactorDistribution"};


	// Constructors

		//- Default constructor
		CamberAngleScalingFactorDistribution() noexcept;

		//- Construct from a Polyline,
		//	no additional checking required
		template
		<
			typename T,
			typename = std::enable_if_t
			<
				std::is_same_v<typename RegBase::type, removeCVRef_t<T>>
			>
		>
		explicit CamberAngleScalingFactorDistribution(T&& t);


	// Member functions

		//- Get object name
		String getName() const override;

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename T, typename>
CamberAngleScalingFactorDistribution::
CamberAngleScalingFactorDistribution(T&& t)
:
	DVBase {std::forward<T>(t)}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
