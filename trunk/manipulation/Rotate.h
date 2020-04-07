/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Rotate

Description
	Class Rotate for rotation of geometry

SourceFiles
	Rotate.cpp

\*---------------------------------------------------------------------------*/

#ifndef ROTATE_H
#define ROTATE_H

#include <memory>
#include <optional>

#include "Axis.h"
#include "ManipulatorBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Rotate Declaration
\*---------------------------------------------------------------------------*/

class Rotate final
:
	public ManipulatorBase<double, std::optional<Axis>>
{
private:

	// Private data

		double angle_;
		std::unique_ptr<Axis> axis_;


protected:

	// Member functions

		//- Manipulate geometry
		void executeManipulation
		(
			const Vectorpair<int>& dimTags
		) const override;


public:

	// Constructors

		//- Default constructor
		Rotate() = default;


	//- Destructor
	~Rotate() = default;


	// Member functions

		//- Set rotation parameters,
		//  rotate by 'angle' radians around z-axis by default,
		void setParameters
		(
			const double& angle,
			const std::optional<Axis>& axis = std::nullopt
		) noexcept override;

		//- Check if parameters are set
		bool isSet() const noexcept override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
