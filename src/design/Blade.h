/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::Blade

Description
	Blade class

SourceFiles
	Blade.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_BLADE_H
#define DESIGN_BLADE_H

#include <utility>

#include "Airfoil.h"
#include "General.h"
#include "Registry.h"
#include "TurboBase.h"
#include "Volume.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
						Class Blade Declaration
\*---------------------------------------------------------------------------*/

class Blade final
:
	public TurboBase
{
private:

	// Private data

		Uptrvector<Airfoil> airfoils_;
		Sptr<geometry::Volume> geometry_;


	// Member functions

		//- Construct the component
		void construct();


public:

	// Constructors

		//- Default constructor,
		//	creates an owned registry and creates a model
		explicit Blade
		(
			const Path& parentCwd = std::filesystem::current_path(),
			const std::size_t id = 0
		);

		//- Construct with (owner) registry,
		//	creates a non-owned accessible registry and
		//	creates an owned model.
		Blade
		(
			const input::Registry& reg,
			const Path& parentCwd = std::filesystem::current_path(),
			const std::size_t id = 0
		);

		//- Construct with (owner) registry,
		//	creates a non-owned accessible registry and
		//	takes or shares ownership of a model
		template<typename T>
		Blade
		(
			const input::Registry& reg,
			T&& model,
			const Path& parentCwd = std::filesystem::current_path(),
			const std::size_t id = 0
		);


	//- Destructor
	~Blade() = default;


	// Member functions

		//- Get a const reference to airfoils
		const Uptrvector<Airfoil>& airfoilsCRef() const;

		//- Get a reference to airfoils
		Uptrvector<Airfoil>& airfoilsRef();

		//- Build blade geometry, doesn't build airfoils
		void build();

		//- Get blade geometry
		Sptr<geometry::Volume> geometry() const noexcept;

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename T>
Blade::Blade
(
	const input::Registry& reg,
	T&& model,
	const Path& parentCwd,
	const std::size_t id
)
:
	TurboBase
	{
		"blade.step",
		reg,
		std::forward<T>(model),
		parentCwd,
		id
	}
{
	construct();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
