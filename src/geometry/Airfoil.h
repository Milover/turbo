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
#include <vector>

#include "ComponentBase.h"
#include "Deviation.h"
#include "Profile.h"
#include "ProfileGenerator.h"
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

		std::unique_ptr<ProfileGenerator> generator_;
		std::unique_ptr<Deviation> deviation_;


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

		//- Limit fluid angle value [0,90]
		double limitAngle(const double angle) const noexcept;

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

	// Public data

		Profile profile;


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

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
