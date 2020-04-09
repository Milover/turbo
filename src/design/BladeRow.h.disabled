/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::BladeRow

Description
	BladeRow class

SourceFiles
	BladeRow.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_BLADE_ROW_H
#define DESIGN_BLADE_ROW_H

#include <string>
#include <memory>

#include "Blade.h"
#include "ComponentBase.h"
#include "InputObjectBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
						Class BladeRow Declaration
\*---------------------------------------------------------------------------*/

class BladeRow final
:
	public ComponentBase
{
private:

	// Private data

		std::unique_ptr<Blade> blade_;


	// Member functions

		//- Check if hub tip ratio is valid
		void checkHubTipRatio() const;

		//- Compute area
		double computeArea() const;

		//- Compute axial velocity
		double computeAxialVelocity() const;

		//- Compute hub radius
		double computeHubRadius() const;

		//- Compute span
		double computeSpan() const;


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
		BladeRow
		(
			const Stringmap<>& input,
			const ComponentBase& owner
		);

		//- Move constructor
		BladeRow(BladeRow&&) = delete;


	//- Destructor
	~BladeRow() = default;


	// Member functions

		//- Build geometry
		void build() override;

		//- Get const pointer to blade
		const Blade* getBlade() const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
