/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::BoundaryLayerField

Description
	BoundaryLayerField class.

SourceFiles
	BoundaryLayerField.cpp

\*---------------------------------------------------------------------------*/

#ifndef MESH_FIELDS_BOUNDARY_LAYER_FIELD_H
#define MESH_FIELDS_BOUNDARY_LAYER_FIELD_H

#include <type_traits>

#include "Curve.h"
#include "Error.h"
#include "General.h"
#include "Point.h"
#include "Registry.h"
#include "SizeField.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace mesh
{

/*---------------------------------------------------------------------------*\
					Class BoundaryLayerField Declaration
\*---------------------------------------------------------------------------*/

class BoundaryLayerField
:
	public SizeField
{
private:

	template<typename PtrType, typename Ptr>
	inline static constexpr bool isValidPtr_v = std::is_same_v
	<
		Sptr<PtrType>, removeCVRef_t<Ptr>
	>;

	// Private data

		Sptrvector<geometry::Curve> edges_;
		Sptrvector<geometry::Point> corners_;

		inline static const String type_ {"BoundaryLayer"};

		// contour discretization / fan points per 2*pi
		// NOTE: guesstimate
		inline static constexpr Float fanFactor_ {10.0};


public:

	// Constructors

		//- Construct form a registry
		BoundaryLayerField(const input::Registry& reg);


	// Member functions

		//- Set field
		void setField() noexcept(ndebug) override;

		//- Set corners (points) on which
		//	a fan should be created
		//	Overwrites the previous corners (if any).
		void setCorners(const Sptrvector<geometry::Point>& points) noexcept;

		//- Set corners (points) on which
		//	a fan should be created
		//	Overwrites the previous corners (if any).
		template
		<
			typename... Points,
			typename = std::enable_if_t
			<
				(isValidPtr_v<geometry::Point, Points> && ...)
			>
		>
		void setCorners(Points&&... ps) noexcept;

		//- Set edges (curves) on which
		//	the boundary layer should be generated.
		//	Overwrites the previous edeges (if any).
		void setEdges(const Sptrvector<geometry::Curve>& points) noexcept;

		//- Set edges (curves) on which
		//	the boundary layer should be generated.
		//	Overwrites the previous edeges (if any).
		template
		<
			typename... Curves,
			typename = std::enable_if_t
			<
				(isValidPtr_v<geometry::Curve, Curves> && ...)
			>
		>
		void setEdges(Curves&&... cs) noexcept;

		//- Get type
		[[nodiscard]] String type() const noexcept override;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename... Points, typename>
void BoundaryLayerField::setCorners(Points&&... ps) noexcept
{
	corners_.clear();
	corners_.reserve(sizeof...(ps));

	(corners_.emplace_back(std::forward<Points>(ps)), ...);
}


template<typename... Curves, typename>
void BoundaryLayerField::setEdges(Curves&&... cs) noexcept
{
	edges_.clear();
	edges_.reserve(sizeof...(cs));

	(edges_.emplace_back(std::forward<Curves>(cs)), ...);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
