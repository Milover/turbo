/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Blade

Description
	Blade class

SourceFiles
	Blade.cpp

\*---------------------------------------------------------------------------*/

#ifndef BLADE_H
#define BLADE_H

#include <string>

#include "Airfoil.h"
#include "ComponentBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Blade Declaration
\*---------------------------------------------------------------------------*/

class Blade final
:
	public ComponentBase
{
private:

	typedef Ptrvector<Airfoil>::iterator iterator;
	typedef Ptrvector<Airfoil>::const_iterator const_iterator;


	// Private data

		//std::unique_ptr<Face> lower_;		// <- implement later
		//std::unique_ptr<Face> top_;		// <- implement later
		//std::unique_ptr<Face> upper_;		// <- implement later

		Ptrvector<Airfoil> airfoils_;

		int numberOfStations_ {10};
		int station_;


	// Member functions

		//- Check number of stations
		void checkNumberOfStations() const;

		//- Check offsets
		void checkOffsets() const;

		//- Compute blade velocity at radius
		double computeBladeVelocity() const;

		//- Compute pitch at radius
		double computePitch() const;

		//- Compute radius at station
		double computeRadius() const;


protected:

	// Member functions

		//- Build input map
		void buildInputMap() noexcept override;

		//- Check values
		void check() const override;

		//- Compute and store values to input map
		void computeAndStore();

		//- Parse input
		void parse(const Stringmap<>& input) override;


public:

	// Constructors

		//- Construct from input
		Blade
		(
			const Stringmap<>& input,
			const ComponentBase& owner
		);

		//- Move constructor
		Blade(Blade&&) = delete;


	//- Destructor
	~Blade() = default;


	// Member functions

		//- Get iterator to beginning
		iterator begin();

		//- Get const iterator to beginning
		const_iterator begin() const;

		//- Build geometry
		void build() override;

		//- Check if empty
		bool empty() const noexcept;

		//- Get iterator to end
		iterator end();

		//- Get const iterator to end
		const_iterator end() const;

		//- Get const pointer to airfoil at station
		const Airfoil* getAirfoilAt(const int station) const;

		//- Get dimTags
		Vectorpair<int> getDimTags() const noexcept override;	// <- provisional

		//- Get number of stations
		int size() const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
