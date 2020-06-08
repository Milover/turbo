/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::MaxPassageWidthDistribution

Description
	Class MaxPassageWidthDistribution.

SourceFiles
	MaxPassageWidthDistribution.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_MAX_PASSAGE_WIDTH_DISTRIBUTION_H
#define INPUT_MAX_PASSAGE_WIDTH_DISTRIBUTION_H

#include <utility>

#include "Error.h"
#include "General.h"
#include "DistributedValue.h"
#include "MaxPassageWidth.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class MaxPassageWidthDistribution Declaration
\*---------------------------------------------------------------------------*/

class MaxPassageWidthDistribution final
:
	public DistributedValue<MaxPassageWidth>
{
public:

	// Public static data

		inline static const String name {"MaxPassageWidthDistribution"};


	// Constructors

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
		explicit MaxPassageWidthDistribution(T&& t);


	// Member functions

		//- Get object name
		String getName() const override;

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename T, typename>
MaxPassageWidthDistribution::MaxPassageWidthDistribution(T&& t)
:
	DVBase {std::forward<T>(t)}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
