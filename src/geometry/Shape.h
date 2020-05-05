/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Shape

Description
	Abstract base class for geometry objects.

	WARNING:
		Does not check wheather a Model is active nor wheather a Model has
		removed the geometry by going out of scope; Godspeed brave adventurer.

		See full disclaimer in 'Model.h'.

SourceFiles
	Shape.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_SHAPE_H
#define GEOMETRY_SHAPE_H

#include <type_traits>

#include "GmshBase.h"
#include "GmshRemove.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Shape Declaration
\*---------------------------------------------------------------------------*/


template
<
	typename Entity,
	typename Remover = interface::GmshRemove
>
class Shape
:
	public Entity,
	public interface::GmshBase
{
protected:

	using ShapeBase = Shape<Entity, Remover>;

	static_assert
	(
		std::is_same_v<Entity0D, Entity>
	 || std::is_same_v<Entity1D, Entity>
	 || std::is_same_v<Entity2D, Entity>
	 || std::is_same_v<Entity3D, Entity>
	);

	static_assert
	(
		std::is_nothrow_default_constructible_v<Remover>
	 && std::is_nothrow_destructible_v<Remover>
	 && std::is_nothrow_invocable_v<Remover, Entity*>
	);


	// Constructors

		//- Default constructor
		Shape() = default;

		//- Construct from tag
		Shape(const std::size_t) noexcept;


public:

	using Coordinates = Vector;


	// Constructors

		//- Disallow copy construction
		Shape(const Shape&) = delete;

		//- Move constructor
		Shape(Shape&&) = default;


	//- Destructor
	virtual ~Shape() noexcept;


	// Member operators

		//- Disallow copy assignment
		Shape& operator=(const Shape&) = delete;

		//- Move assignment operator
		Shape& operator=(Shape&&) = delete;

};

// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

template
<
	typename Entity,
	typename Remover
>
Shape<Entity, Remover>::Shape(const std::size_t tag) noexcept
:
	Entity {tag}
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

template
<
	typename Entity,
	typename Remover
>
Shape<Entity, Remover>::~Shape() noexcept
{
	if (this->tag_ != 0)
	{
		Remover {}(this);
		this->sync_ = false;
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
