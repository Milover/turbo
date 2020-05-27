/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Model

Description
	Model class

	WARNING:
		Essentially a useless class since the geometry implements add, remove
		and similar actions, but is necessary because gmsh implements models
		for the accounting of entities and some important actions like
		'write()', 'listEntities()' etc. As suchthis class functions only as a
		light handle to the gmsh model.
		It should be noted that when going out of scope it will remove all
		contained geometry, but the geometry itself does not implement any
		checks whatsoever to see wheather a valid model exists nor wheather
		the previously valid model has removed all of it's geometry. It is
		presuposed that a valid model exists before any geometry creation and
		that it remains valid (i.e. doesn't go out of scope) until all geometry
		(that the model owns) has gone out of scope.

		Keep this in mind while using this garbage of a class.

	TODO:
		Try to fix this at some point. Maybe a geometry generator class
		so the valid-model-check is done once for batch geometry
		creation/removal? Although the issue is mostly with removal since
		we have to remove unused geometry because of ridiculous synchronization
		costs.

SourceFiles
	Model.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_MODEL_H
#define GEOMETRY_MODEL_H

#include <list>

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Model Declaration
\*---------------------------------------------------------------------------*/

class Model
{
private:

	// Private data

		inline static thread_local std::size_t activeId_ {0};
		inline static thread_local std::size_t count_ {0};
		inline static thread_local std::list<std::size_t> log_ {};

		std::size_t id_;


	// Member functions

		//- Remove the underlying geometry (model)
		void remove() const noexcept;


public:

	// Constructors

		//- Default constructor,
		//	activates the model
		Model() noexcept;

		//- Copy constructor
		Model(const Model&) = delete;

		//- Move constructor,
		//	doesn't activate the model
		Model(Model&&) noexcept;


	//- Destructor
	~Model() noexcept;


	// Member functions

		//- Activate the model if it isn't active,
		//	true if successfull, false otherwise
		bool activate() const noexcept;

		//- Activate the model with id 'id',
		//	true if successful, false otherwise
		static bool activate(const std::size_t id) noexcept;

		//- Activate the model with id 'id',
		//	true if successful, false otherwise
		static std::size_t activeId() noexcept;

		//- Get id
		std::size_t id() const noexcept;

		//- Get name (string id)
		String name() const noexcept;

		//- Write the model data (geometry) to a file,
		//	activates the model. 'extension' determines the filetype,
		//	see gmsh documentation for supported filetypes.
		//	The file name will be 'prefix_[model id]_suffix.extension'.
		void write
		(
			const String& extension,
			const String& prefix = "",
			const String& suffix = ""
		) const noexcept;


	// Member operators

		//- Dissallow copy assignment
		Model& operator=(const Model&) = delete;

		//- Dissallow move assignment
		Model& operator=(Model&&) = delete;

		//- Operator bool.
		//	True if owns geometry (model), false otherwise.
		explicit operator bool() const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
