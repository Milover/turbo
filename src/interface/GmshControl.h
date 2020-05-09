/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshControl

Description
	GmshControl class.
	An interface class for the initialization and management/control of the
	gmsh software.

SourceFiles
	GmshControl.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_CONTROL_H
#define INTERFACE_GMSH_CONTROL_H

#include "Error.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshControl Definition
\*---------------------------------------------------------------------------*/

class [[nodiscard]] GmshControl
{
private:

	// Private data

		inline static thread_local std::size_t count_ {0};
		inline static thread_local bool gui_ {false};
		inline static thread_local GmshControl* ptr_ {nullptr};


	// Constructors

		//- Initialize gmsh and the gmsh-gui if gui is set to true,
		//	will write gmsh output to terminal if terminal is set to true.
		//	Also sets some helpful defaults for gmsh
		explicit GmshControl
		(
			const bool terminal = false,
			const bool gui = false
		) noexcept;


public:

	// Destructor
	~GmshControl() noexcept;


	// Member functions

		//- Initialize gmsh, if it hasn't been initialized and
		//	return a reference
		[[nodiscard]] static GmshControl& initialize
		(
			const bool terminal = false,
			const bool gui = false
		);

		//- Return initialized state
		static bool initialized() noexcept;

		//- Get a property value
		//auto get(String&& key) const noexcept(ndebug);
			// FIXME: reimplement

		//- Initialize gui if it isn't already initialized
		void initializeGui() const noexcept;

		//- Run gmsh gui event loop indefinitely if
		//	gui is initialized, do nothing otherwise
		void run() const noexcept;

		//- Set a (number) property value,
		//	returns true if succesful
		bool set(String&& key, const Float value) const noexcept;

		//- Set a (string) property value,
		//	returns true if succesful
		bool set(String&& key, String&& value) const noexcept;

		//- Update gui and draw graphics if gui is initialized,
		//	do nothing otherwise
		void update() const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
