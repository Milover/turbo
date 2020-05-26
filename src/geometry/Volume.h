/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Volume

Description
	A base class for volume geometry classes.

	NOTE:
		construction with holes not implemented

	WARNING:
		Same deal as with creating surfaces but with curves instead of points.
		See 'Surface.h' for more info.

SourceFiles
	Volume.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_VOLUME_H
#define GEOMETRY_VOLUME_H

#include <type_traits>

#include "Entity.h"
#include "General.h"
#include "PlaceholderVolume.h"
#include "Shape.h"
#include "Surface.h"

#include <gmsh.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * * Type traits * * * * * * * * * * * * * * * * //

template<typename T>
inline constexpr bool isSurfaceSptr_v = std::is_same_v
<
	Sptr<Surface>,
	removeCVRef_t<T>
>;


/*---------------------------------------------------------------------------*\
						Class Volume Declaration
\*---------------------------------------------------------------------------*/

class Volume
:
	public Shape<Entity3D>
{
private:

	// Private data

		Sptrvector<Surface> boundary_;


	// Member functions

		//- Construct volume geometry
		void construct() const noexcept;


protected:

	template<typename T>
	inline static constexpr bool isValid_v =
		isSurfaceSptr_v<T>
	 || std::is_base_of_v<Surface, removeCVRef_t<T>>;

	template<typename T>
	using enableIfValid_t = std::enable_if_t<isValid_v<T>>;


	// Constructors

		//- Default constructor
		Volume() = default;


public:

	// Constructors

		//- Construct from surfaces
		template
		<
			typename... Surfaces,
			typename = std::enable_if_t<(isValid_v<Surfaces> && ...)>
		>
		Volume(Surfaces&&... ss);

		//- Construct from a placeholder volume
		Volume(const detail::PlaceholderVolume& v);

		//- Copy constructor
		Volume(const Volume&) = delete;

		//- Move constructor
		Volume(Volume&&) = default;


	//- Destructor
	virtual ~Volume() noexcept;


	// Member functions

		//- Get the boundary surfaces
		[[nodiscard]] const Sptrvector<Surface>& boundaryCRef() const noexcept;

		//- Get the boundary surfaces
		[[nodiscard]] Sptrvector<Surface>& boundaryRef() noexcept;


	// Member operators

		//- Disallow copy assignment
		Volume& operator=(const Volume&) = delete;

		//- Disallow move assignment
		Volume& operator=(Volume&&) = delete;

};


// * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * //

template<typename... Surfaces, typename>
Volume::Volume(Surfaces&&... ss)
{
	// FIXME: sanity check missing (check if surfaces form a closed loop)

	auto&& makeSptr = [](auto&& surface)
	{
		using SurfaceType = decltype(surface);

		if constexpr (isSurfaceSptr_v<SurfaceType>)
		{
			return surface;
		}
		else
			return Sptr<Surface>
			{
				new removeCVRef_t<SurfaceType>
				{
					std::forward<SurfaceType>(surface)
				}
			};
	};

	boundary_.reserve(sizeof...(ss));

	(
		boundary_.emplace_back
		(
			makeSptr(std::forward<Surfaces>(ss))
		), ...
	);

	construct();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
