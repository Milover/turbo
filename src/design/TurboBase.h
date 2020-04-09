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

#ifndef DESIGN_TURBO_BASE_H
#define DESIGN_TURBO_BASE_H

#include "General.h"
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

		bool owns_;
		Registry* data_;


	// Constructors

		//- Default constructor
		TurboBase() noexcept;

		//- Construct with (owner) Registry
		TurboBase(const Registry&) noexcept;


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
		virtual void build() = 0;

		//- Finalize geometry
		virtual void finalize() = 0;

		//- Access data
		template<typename T, enum Registry::Scope S = Registry::LOCAL>
		T get() const;

		//- Querry data
		template<enum Registry::Scope S = Registry::LOCAL>
		bool has(const Word& key) const noexcept;

		//- Build mesh
		virtual void mesh() = 0;

		//- Parametrize
		virtual void parametrize() = 0;


		//- Optimize
		//virtual void optimize() = 0;


	// Member operators

		//- Disallow copy assignment operator
		TurboBase& operator=(const TurboBase&) = delete;

		//- Disallow move assignment operator
		TurboBase& operator=(TurboBase&&) = delete;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T, enum Registry::Scope S>
T TurboBase::get() const
{
	return data_->get<T, S>();
}


template<enum Registry::Scope S>
bool TurboBase::has(const Word& key) const noexcept
{
	return data_->has<S>(key);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
