/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Scale

Description
	Class Scale for rotation of geometry

SourceFiles
	Scale.cpp

\*---------------------------------------------------------------------------*/

#ifndef SCALE_H
#define SCALE_H

#include <memory>

#include "ManipulatorBase.h"
#include "Point.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Scale Declaration
\*---------------------------------------------------------------------------*/

class Scale final
:
	public ManipulatorBase<Point, double, double, double>
{
private:

	// Private data

		std::unique_ptr<PointCoordinates> point_;
		std::unique_ptr<PointCoordinates> scaleFactors_;


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
		Scale() = default;


	//- Destructor
	~Scale() = default;


	// Member functions

		//- Set scale parameters,
		//  2d scale by default
		void setParameters
		(
			const Point& point,
			const double& fx,
			const double& fy,
			const double& fz = 1.0
		) noexcept override;

		//- Set uniform 2d scale parameters
		void setParameters
		(
			const Point& point,
			const double factor
		) noexcept;

		//- Set uniform 2d scale factor,
		//  scale about origin
		void setParameters(const double factor) noexcept;

		//- Check if parameters are set
		bool isSet() const noexcept override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
