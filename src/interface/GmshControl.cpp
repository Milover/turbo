/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <gmsh.h>

#include "GmshControl.h"

#include "Error.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * * Private Constructors  * * * * * * * * * * * * * //

GmshControl::GmshControl
(
	const bool terminal,
	const bool gui
) noexcept
{
	GmshControl::gui_ = gui;
	GmshControl::ptr_ = this;

	gmsh::initialize(0, 0, false);

	if (terminal)
	{
		gmsh::option::setNumber("General.Terminal",						1);
		gmsh::option::setNumber("General.Verbosity",					1);
	}

	if (gui)
	{
		gmsh::fltk::initialize();
		gmsh::option::setNumber("Geometry.NumSubEdges",					200);
		gmsh::option::setNumber("Geometry.Surfaces",					1);
		gmsh::option::setNumber("Geometry.SurfaceNumbers",				1);
		gmsh::option::setNumber("Geometry.SurfaceType",					2);
		gmsh::option::setNumber("Geometry.Volumes",						1);
	}

	gmsh::option::setNumber("General.MouseInvertZoom",					1);
	gmsh::option::setNumber("General.NumThreads",						0);
	gmsh::option::setNumber("Geometry.AutoCoherence",					0);
	gmsh::option::setNumber("Geometry.Tolerance",						1e-17);
	gmsh::option::setNumber("Mesh.Algorithm",							6);
	gmsh::option::setNumber("Mesh.AlgorithmSwitchOnFailure",			0);
	gmsh::option::setNumber("Mesh.AnisoMax",							100);
	gmsh::option::setNumber("Mesh.CharacteristicLengthFromCurvature",	1);
	gmsh::option::setNumber("Mesh.CharacteristicLengthExtendFromBoundary", 0);
	gmsh::option::setNumber("Mesh.CharacteristicLengthFromPoints",		0);
//	gmsh::option::setNumber("Mesh.CharacteristicLengthMax",				1e5);
//	gmsh::option::setNumber("Mesh.CharacteristicLengthMin",				1e-7);
	gmsh::option::setNumber("Mesh.MinimumCirclePoints",					20);
	gmsh::option::setNumber("Mesh.MinimumCurvePoints",					10);
	gmsh::option::setNumber("Mesh.MinimumElementsPerTwoPi",				20);
	gmsh::option::setNumber("Mesh.MshFileVersion",						2);
	gmsh::option::setNumber("Mesh.OptimizeNetgen",						1);
	gmsh::option::setNumber("Mesh.RefineSteps",							25);
	gmsh::option::setNumber("Mesh.Smoothing",							10);
	gmsh::option::setNumber("Mesh.SmoothNormals",						1);
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

GmshControl::~GmshControl() noexcept
{
	--GmshControl::count_;

	if (GmshControl::count_ == 0)
	{
		delete GmshControl::ptr_;
		GmshControl::ptr_ = nullptr;

		gmsh::finalize();
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

[[nodiscard]] GmshControl& GmshControl::initialize
(
	const bool terminal,
	const bool gui
)
{
	++GmshControl::count_;

	if (!GmshControl::ptr_)
		GmshControl::ptr_ = new GmshControl {terminal, gui};

	return *GmshControl::ptr_;
}


bool GmshControl::initialized() noexcept
{
	return bool(GmshControl::ptr_);
}

/*
auto GmshControl::get(String&& key) const noexcept(ndebug)
{
	try
	{
		Float fValue;
		gmsh::option::getNumber
		(
			std::move(key),
			fValue
		);

		return fValue;
	}
	catch(...) {}

	try
	{
		String sValue;
		gmsh::option::getString
		(
			std::move(key),
			sValue
		);

		return sValue;
	}
	catch(...)
	{
		error(FUNC_INFO, "invalid key: ", key);
	}
}
*/


void GmshControl::initializeGui() const noexcept
{
	if (!GmshControl::gui_)
	{
		GmshControl::gui_ = true;
		gmsh::fltk::initialize();
	}
}


void GmshControl::run() const noexcept
{
	if (GmshControl::gui_)
		gmsh::fltk::run();
}


bool GmshControl::set(String&& key, const Float value) const noexcept
{
	try
	{
		gmsh::option::setNumber
		(
			std::move(key),
			value
		);

		return true;
	}
	catch(...)
	{
		return false;
	}
}


bool GmshControl::set(String&& key, String&& value) const noexcept
{
	try
	{
		gmsh::option::setString
		(
			std::move(key),
			value
		);

		return true;
	}
	catch(...)
	{
		return false;
	}
}


void GmshControl::update() const noexcept
{
	if (GmshControl::gui_)
	{
		gmsh::fltk::update();
		gmsh::graphics::draw();
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
