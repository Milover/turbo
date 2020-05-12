# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# add sources
set(SRC
	GmshAddField.cpp
	GmshBase.cpp
	GmshBezier.cpp
	GmshBoundary.cpp
	GmshBoundingBox.cpp
	GmshControl.cpp
	GmshCopy.cpp
	GmshExtrude.cpp
	GmshGenerate.cpp
	GmshLine.cpp
	GmshPlanarSurface.cpp
	GmshPoint.cpp
	GmshPhysicalGroup.cpp
	GmshRecombine.cpp
	GmshRemove.cpp
	GmshRemoveField.cpp
	GmshRemovePhysicalGroup.cpp
	GmshSetBGMesh.cpp
	GmshSetBLMesh.cpp
	GmshSetFieldNumber.cpp
	GmshSetFieldNumbers.cpp
	GmshSetFieldString.cpp
	GmshSetOptionNumber.cpp
	GmshSmooth.cpp
	GmshSpline.cpp
	GmshTransfinite.cpp
	GmshWrite.cpp
	)

# append to sources
file(GLOB HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
append_turbo_src(${CMAKE_CURRENT_SOURCE_DIR} "${SRC};${HDR}")
