/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::SizeFieldBase

Description
	Abstract base class for size field classes.

SourceFiles
	SizeFieldBase.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_FIELDS_SIZE_FIELD_BASE_H
#define MESH_FIELDS_SIZE_FIELD_BASE_H

#include <type_traits>
#include <utility>

#include "General.h"
#include "GmshBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

/*---------------------------------------------------------------------------*\
					Class SizeFieldBase Declaration
\*---------------------------------------------------------------------------*/

class SizeFieldBase
:
	public interface::GmshBase
{
private:

	template<typename T>
	inline static constexpr bool isValid_v =
		std::is_same_v<Float, removeCVRef_t<T>>
	 || std::is_same_v<String, removeCVRef_t<T>>;


	// Private data

		std::size_t tag_;
		inline static std::size_t count_ {0};


protected:

	// Protected data

		bool set_ {false};


	// Constructors

		//- Default constructor
		SizeFieldBase() noexcept;


public:

	// Constructors

		//- Disallow copy constructor
		SizeFieldBase(const SizeFieldBase&) = delete;

		//- Move constructor
		SizeFieldBase(SizeFieldBase&&) noexcept;


	//- Destructor
	virtual ~SizeFieldBase() noexcept;


	// Member functions

		//- Set field as mesh size field
		virtual void setField() = 0;

		//- Get count
		[[nodiscard]] static std::size_t count() noexcept;

		//- Check if field is set
		[[nodiscard]] bool set() const noexcept;

		//- Get tag
		[[nodiscard]] std::size_t tag() const noexcept;

		//- Get type
		[[nodiscard]] virtual String type() const noexcept = 0;


	// Member operators

		//- Disallow copy assignment operator
		SizeFieldBase& operator=(const SizeFieldBase&) = delete;

		//- Disallow move assignment operator
		SizeFieldBase& operator=(SizeFieldBase&&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
