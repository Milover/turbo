/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::SurfaceSection

Description
	SurfaceSection class

SourceFiles
	SurfaceSection.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_SURFACE_SECTION_H
#define GEOMETRY_SURFACE_SECTION_H

#include <utility>
#include <vector>
#include <type_traits>

#include <gmsh.h>			// :(

#include "Curve.h"
#include "General.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class SurfaceSection Definition
\*---------------------------------------------------------------------------*/

class SurfaceSection final
:
	public Surface
{
private:

	// Member functions

		//- Construct surface geometry
		template<typename T>
		Integer construct(std::vector<T>&& curves) const noexcept;


public:

	// Constructors

		//- Construct from a vector of curves and
		//	a vector of corner point tags
		template
		<
			typename T,
			std::enable_if_t<std::is_base_of_v<Curve, T>, int> = 0
		>
		SurfaceSection
		(
			std::vector<T>&& curves,
			const Intvector& cornerTags
		) noexcept;

		//- Copy constructor
		SurfaceSection(const SurfaceSection&) = delete;

		//- Copy constructor
		SurfaceSection(SurfaceSection&&) = default;


	//- Destructor
	~SurfaceSection() = default;


	// Member operators

		//- Disallow copy assignment
		SurfaceSection& operator=(const SurfaceSection&) = delete;

		//- Disallow move assignment
		SurfaceSection& operator=(SurfaceSection&&) = delete;

};


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<typename T>
Integer SurfaceSection::construct(std::vector<T>&& curves) const noexcept
{
	Intvector tags;
	Vectorpair<Integer> outDimTags;

	// remove the curves afterwards because we make new ones
	for (auto& c : curves)
		tags.push_back(c.tag());

	gmsh::model::occ::addThruSections
	(
		tags,
		outDimTags,
		-1,			// don't assign tag
		false,		// don't make solid
		false		// don't make ruled
	);

	return outDimTags.front().second;
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template
<
	typename T,
	std::enable_if_t<std::is_base_of_v<Curve, T>, int>
>
SurfaceSection::SurfaceSection
(
	std::vector<T>&& curves,
	const Intvector& cornerTags
) noexcept
:
	Surface
	{
		construct
		(
			std::move(curves)
		),
		cornerTags
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
