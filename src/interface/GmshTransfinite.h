/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshTransfinite

Description
	GmshTransfinite class

	NOTE: transfinite volumes not implemented

SourceFiles
	GmshTransfinite.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_TRANSFINITE_H
#define INTERFACE_GMSH_TRANSFINITE_H

#include <type_traits>
#include <utility>

#include "Curve.h"
#include "Error.h"
#include "General.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshTransfinite Declaration
\*---------------------------------------------------------------------------*/

class GmshTransfinite
{
private:

	template<typename T>
	inline static constexpr bool isCurvePtr_v = std::is_same_v
	<
		geometry::Curve*, removeCVRef_t<T>
	>;

	template<typename T>
	inline static constexpr bool isSurfacePtr_v = std::is_same_v
	<
		geometry::Surface*, removeCVRef_t<T>
	>;


	//- Execute
	//	NOTE: calls GmshBase::synchronize()
	void execute
	(
		const geometry::Curve* curve,
		const String& distribution,
		const Integer numSegments,
		const Float scaleFactor
	) const noexcept(ndebug);

	//- Execute
	//	NOTE: calls GmshBase::synchronize()
	void execute(const geometry::Surface* surface) const noexcept(ndebug);

	//- Execute
	//	NOTE: calls GmshBase::synchronize()
	//	XXX: corners not implemented for volumes
	//void execute(const Volume* volume) const noexcept(ndebug)


public:

	enum class Distribution
	{
		PROGRESSION,
		BUMP
	};

	//- Designate a curves for transfinite meshing
	//	non-uniform discretization
	template
	<
		typename... Curves,
		typename = std::enable_if_t<(isCurvePtr_v<Curves> && ...)>
	>
	void operator()
	(
		const Distribution distribution,
		const Integer numSegments,
		const Float scaleFactor,
		Curves&&... cs
	) const noexcept(ndebug);

	//- Designate a curves for transfinite meshing,
	//	uniform discretization
	template<typename... Curves>
	void operator()
	(
		const Integer numSegments,
		Curves&&... cs
	) const noexcept(ndebug);

	//- Designate a surfaces for transfinite meshing
	template
	<
		typename... Surfaces,
		typename = std::enable_if_t<(isSurfacePtr_v<Surfaces> && ...)>
	>
	void operator()(Surfaces&&... ss) const noexcept(ndebug);

	//- Designate a volume for transfinite meshing
	//	XXX: corners not implemented for volumes
	//void operator()(const Volume* volume) const noexcept(ndebug);

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename... Curves>
void GmshTransfinite::operator()
(
	const Integer numSegments,
	Curves&&... cs
) const noexcept(ndebug)
{
	this->operator()
	(
		GmshTransfinite::Distribution::PROGRESSION,		// irrelevant
		numSegments,
		1.0,
		std::forward<Curves>(cs)...
	);
}


template<typename... Curves, typename>
void GmshTransfinite::operator()
(
	const Distribution distribution,
	const Integer numSegments,
	const Float scaleFactor,
	Curves&&... cs
) const noexcept(ndebug)
{
	if (numSegments <= 0)
		error(FUNC_INFO, "number of segments < 0");

	String distributionType;

	if (distribution == GmshTransfinite::Distribution::PROGRESSION)
		distributionType = "Progression";
	else
		distributionType = "Bump";

	(
		execute
		(
			std::forward<Curves>(cs),
			distributionType,
			numSegments,
			scaleFactor
		),
		...
	);
}


template<typename... Surfaces, typename>
void GmshTransfinite::operator()(Surfaces&&... ss) const noexcept(ndebug)
{
	(execute(std::forward<Surfaces>(ss)), ...);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
