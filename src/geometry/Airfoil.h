/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Airfoil

Description
	Class Airfoil

SourceFiles
	Airfoil.cpp

\*---------------------------------------------------------------------------*/

#ifndef AIRFOIL_H
#define AIRFOIL_H

#include <string>
#include <memory>

#include "ComponentBase.h"
#include "Deviation.h"
#include "Line.h"
#include "Point.h"
#include "ProfileGenerator.h"
#include "Spline.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Airfoil Declaration
\*---------------------------------------------------------------------------*/

class Airfoil final
:
	public ComponentBase
{
private:

	// Private data

		Ptrvector<Point> points_;

		std::unique_ptr<Spline> surface_;
		std::unique_ptr<Line> trailing_;

		std::unique_ptr<ProfileGenerator> generator_;
		std::unique_ptr<Deviation> deviation_;

		bool wrapped_;


	// Member functions

		//- Compute blade inlet angle
		double computeBladeInletAngle() const;

		//- Compute total-to-static pressure difference
		double computeDeltaP() const;

		//- Compute fluid inlet angle
		double computeFluidInletAngle() const;

		//- Compute fluid outlet angle
		double computeFluidOutletAngle() const;

		//- Compute profile angles
		void computeProfile();

		//- Compute fluid outlet angle from Euler's work equation
		double eulerEquation() const;

		//- Initialize pointers
		void initializePointers(const Stringmap<>& input);

		//- Generate points
		void generatePoints() noexcept;	

		//- Generate points
		void generateLines() noexcept;	

		//- Limit fluid angle value [0,90]
		double limitAngle(const double angle) const noexcept;

		//- Position geometry (scale, stack, rotate)
		void positionProfile() const;

		//- Compute fluid outlet angle from vortex law equation
		double vortexEquation() const;


protected:

	// Member functions

		//- Build input map
		void buildInputMap() noexcept override;

		//- Check values
		void check() const override;

		//- Compute and store values to input map
		void computeAndStore();


public:
	
	// Constructors

		//- Construct from input
		Airfoil
		(
			const Stringmap<>& input,
			const ComponentBase& owner
		);

		//- Move constructor
		Airfoil(Airfoil&&) = delete;


	//- Destructor
	~Airfoil() = default;


	// Member functions

		//- Build geometry
		void build() override;

		//- Compute swirl constant
		double computeSwirl() const;

		//- Get dimTags
		Vectorpair<int> getDimTags() const noexcept override;	// <- provisional

		//- Get geometric center
		Point getCenter() const noexcept;

		//- Get leading edge
		Point getLeadingEdge() const;

		//- Get lower trailing edge
		Point getLowerTrailingEdge() const;

		//- Get upper trailing edge
		Point getUpperTrailingEdge() const;

		//- Return wrapped state
		bool isWrapped() const noexcept;

		//- Project to cylinder
		//void wrapToCylinder() const;		// <- implement later

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
