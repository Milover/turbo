/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::SolidityDistribution

Description
	Class SolidityDistribution.

	Defaults to 1.0.

SourceFiles
	SolidityDistribution.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_SOLIDITY_DISTRIBUTION_H
#define INPUT_SOLIDITY_DISTRIBUTION_H

#include <utility>

#include "Error.h"
#include "General.h"
#include "DistributedValue.h"
#include "Solidity.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class SolidityDistribution Declaration
\*---------------------------------------------------------------------------*/

class SolidityDistribution final
:
	public DistributedValue<Solidity>
{
public:

	// Public static data

		inline static const String name {"SolidityDistribution"};


	// Constructors

		//- Default constructor
		SolidityDistribution() noexcept;

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
		explicit SolidityDistribution(T&& t);


	// Member functions

		//- Get object name
		String getName() const override;

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename T, typename>
SolidityDistribution::SolidityDistribution(T&& t)
:
	DVBase {std::forward<T>(t)}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
