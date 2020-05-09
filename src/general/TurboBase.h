/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::TurboBase

Description
	Abstract base class various turbo classes.

SourceFiles
	TurboBase.cpp

\*---------------------------------------------------------------------------*/

#ifndef TURBO_BASE_H
#define TURBO_BASE_H

#include <type_traits>
#include <utility>

#include "General.h"
#include "Model.h"
#include "Registry.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

/*---------------------------------------------------------------------------*\
					Class TurboBase Declaration
\*---------------------------------------------------------------------------*/

class TurboBase
{
private:

	template<typename T>
	inline static constexpr bool isValid_v =
		std::is_same_v<Sptr<geometry::Model>, removeCVRef_t<T>>
	 || std::is_same_v<geometry::Model&&, T> 
	 || std::is_same_v<geometry::Model, T>;


protected:

	// Protected data

		bool ownsData_;
		input::Registry* data_;
		Sptr<geometry::Model> model_;

		Path file_;


	// Constructors

		//- Default constructor,
		//	creates an owned registry and creates a model
		TurboBase(const Path& file = Path {});

		//- Construct with (owner) registry,
		//	creates a non-owned accessible registry and
		//	creates an owned model.
		TurboBase
		(
			const input::Registry& reg,
			const Path& file = Path {}
		);

		//- Construct with (owner) registry,
		//	creates a non-owned accessible registry and
		//	takes or shares ownership of a model
		template
		<
			typename T,
			typename = std::enable_if_t<isValid_v<T>>
		>
		TurboBase
		(
			const input::Registry& reg,
			T&& model,
			const Path& file = Path {}
		);


	// Member functions

		//- Adjust filename
		void adjustFilename
		(
			const String& prefix,
			const String& extension
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
		virtual void build() = 0;

		//- Get file
		[[nodiscard]] Path file() const;

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

		//- Parametrize
		//virtual void parametrize() = 0;

		//- Optimize
		//virtual void optimize() = 0;

		//- Write geometry to file
		virtual void write() const = 0;


	// Member operators

		//- Disallow copy assignment operator
		TurboBase& operator=(const TurboBase&) = delete;

		//- Disallow move assignment operator
		TurboBase& operator=(TurboBase&&) = delete;

};


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

template<typename T, typename>
TurboBase::TurboBase
(
	const input::Registry& reg,
	T&& model,
	const Path& file
)
:
	ownsData_ {false},
	data_					// we don't own or manage but have access
	{
		&const_cast<input::Registry&>(reg).create()
	}
{
	if constexpr
	(
		std::is_same_v<Sptr<geometry::Model>, removeCVRef_t<T>>
	)
	{
		model_ = std::forward<T>(model);
	}
	else
		model_.reset
		(
			new geometry::Model {std::forward<T>(model)}
		);

	if (std::filesystem::is_directory(file))
		file_ = file / "";
}


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

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
