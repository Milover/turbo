/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::TurboBase

Description
	Abstract base class template for generic turbomachinery components.

SourceFiles
	TurboBase.cpp

\*---------------------------------------------------------------------------*/

#ifndef TURBO_BASE_H
#define TURBO_BASE_H

#include <type_traits>

#include "General.h"
#include "Model.h"
#include "Registry.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
					Class TurboBase Declaration
\*---------------------------------------------------------------------------*/

class TurboBase
{
protected:

	// Protected data

		bool ownsData_;
		input::Registry* data_;
		Uptr<geometry::Model> model_;


	// Constructors

		//- Default constructor,
		//	creates an owned Registry and
		//	creates a model
		TurboBase();

		//- Construct with (owner) Registry,
		//	creates a non-owned, accessible registry and
		//	doesn't create a model
		TurboBase(const input::Registry& reg);

		//- Construct with (owner) Registry,
		//	creates a non-owned accessible registry and
		//	take ownership of a model
		TurboBase
		(
			const input::Registry& reg,
			geometry::Model&& mod
		);


public:

	// Constructors

		//- Disallow copy constructor
		TurboBase(const TurboBase&) = delete;

		//- Disallow move constructor
		TurboBase(TurboBase&&) = delete;


	//- Destructor
	virtual ~TurboBase() noexcept;


	// Member functions

		//- Build geometry
		//virtual void build() = 0;

		//- Finalize geometry
		//virtual void finalize() = 0;

		//- Access data
		template<typename T, typename R = NoRecurse>
		std::enable_if_t<std::is_base_of_v<RecursionFlag, R>, T>
		get() const;

		//- Querry data
		template<typename R = NoRecurse>
		std::enable_if_t<std::is_base_of_v<RecursionFlag, R>, bool>
		has(const String& key) const;

		//- Build mesh
		//virtual void mesh() = 0;

		//- Parametrize
		//virtual void parametrize() = 0;

		//- Optimize
		//virtual void optimize() = 0;


	// Member operators

		//- Disallow copy assignment operator
		TurboBase& operator=(const TurboBase&) = delete;

		//- Disallow move assignment operator
		TurboBase& operator=(TurboBase&&) = delete;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T, typename R>
std::enable_if_t<std::is_base_of_v<RecursionFlag, R>, T>
TurboBase::get() const
{
	return data_->get<T, R>();
}


template<typename R>
std::enable_if_t<std::is_base_of_v<RecursionFlag, R>, bool>
TurboBase::has(const String& key) const
{
	return data_->has<R>(key);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
