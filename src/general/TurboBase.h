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

#include <filesystem>
#include <type_traits>
#include <ostream>
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
public:

	enum class Cwd
	{
		CREATE,
		NO_CREATE
	};


private:

	template<typename T>
	inline static constexpr bool isValid_v =
		std::is_same_v<Sptr<geometry::Model>, removeCVRef_t<T>>
	 || std::is_same_v<geometry::Model&&, T> 
	 || std::is_same_v<geometry::Model, T>;


	// Private data

		bool restart_ {false};


	// Member functions

		//- Handle cwd creation
		void handleCwd
		(
			const Path& parentCwd,
			const Cwd cwd
		);


protected:

	// Protected data

		bool ownsData_;
		input::Registry* data_;
		Sptr<geometry::Model> model_;

		Path cwd_;
		const std::size_t id_;


	// Constructors

		//- Default constructor,
		//	creates an owned registry and creates a model
		TurboBase
		(
			const Path& file,
			const Path& parentCwd = std::filesystem::current_path(),
			const std::size_t id = 0,
			const Cwd cwd = Cwd::CREATE
		);

		//- Construct with (owner) registry,
		//	creates a non-owned accessible registry and
		//	creates an owned model.
		TurboBase
		(
			const Path& file,
			const input::Registry& reg,
			const Path& parentCwd = std::filesystem::current_path(),
			const std::size_t id = 0,
			const Cwd cwd = Cwd::CREATE
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
			const Path& file,
			const input::Registry& reg,
			T&& model,
			const Path& parentCwd = std::filesystem::current_path(),
			const std::size_t id = 0,
			const Cwd cwd = Cwd::CREATE
		);


public:

	// Public data

		const Path filename;


	// Constructors

		//- Disallow copy constructor
		TurboBase(const TurboBase&) = delete;

		//- Disallow move constructor
		TurboBase(TurboBase&&) = delete;


	//- Destructor
	virtual ~TurboBase() noexcept;


	// Member functions

		//- Activate local model
		void activate() const;

		//- Access data by cref
		template
		<
			typename T,
			typename R = Recurse,
			typename = std::enable_if_t<std::is_base_of_v<RecursionFlag, R>>
		>
		[[nodiscard]] const T& cref() const;

		//- Get the working directory
		[[nodiscard]] Path cwd() const;

		//- Dump registry data to file (default: cwd_/filename)
		void dumpData(const Path& file = Path {}) const;

		//- Access data
		template
		<
			typename T,
			typename R = Recurse,
			typename = std::enable_if_t<std::is_base_of_v<RecursionFlag, R>>
		>
		[[nodiscard]] T get() const;

		//- Querry data
		template
		<
			typename R = Recurse,
			typename = std::enable_if_t<std::is_base_of_v<RecursionFlag, R>>
		>
		[[nodiscard]] bool has(const String& key) const;

		//- Get id
		[[nodiscard]] std::size_t id() const noexcept;

		//- Print all data from local registry (formatted)
		void printAll
		(
			std::ostream& os,
			const String::size_type width = 50,		// generally enough
			const String& delimiter = " ",
			const String& terminator = ";\n",
			const Integer precision = 9
		) const;

		//- Access data by ref
		template
		<
			typename T,
			typename R = Recurse,
			typename = std::enable_if_t<std::is_base_of_v<RecursionFlag, R>>
		>
		[[nodiscard]] T& ref();

		//- Return restarted state
		[[nodiscard]] bool restarted() const noexcept;

		//- Set the working directory,
		//	NOTE: no checking whatsoever
		void setCwd(const Path& cwd);

		//- Write geometry to file
		virtual void write() const;


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
	const Path& file,
	const input::Registry& reg,
	T&& model,
	const Path& parentCwd,
	const std::size_t id,
	const Cwd cwd
)
:
	ownsData_ {false},
	data_					// we don't own or manage but have access
	{
		&const_cast<input::Registry&>(reg).create()
	},
	id_ {id},
	filename
	{
		addFilenameSuffix(file, id)
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

	handleCwd(parentCwd, cwd);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T, typename R, typename>
const T& TurboBase::cref() const
{
	return data_->cref<T, R>();
}


template<typename T, typename R, typename>
T TurboBase::get() const
{
	return data_->get<T, R>();
}


template<typename R, typename>
bool TurboBase::has(const String& key) const
{
	return data_->has<R>(key);
}


template<typename T, typename R, typename>
T& TurboBase::ref()
{
	return data_->ref<T, R>();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
