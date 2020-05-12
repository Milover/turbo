/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Volume

Description
	A base class for volume geometry classes.

	NOTE: currently only supports construction from placeholder volumes.

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

		//- Construct from a placeholder volume
		Volume(const detail::PlaceholderVolume& v);

		//- Copy constructor
		Volume(const Volume&) = delete;

		//- Move constructor
		Volume(Volume&&) = default;


	//- Destructor
	virtual ~Volume() = default;


	// Member functions

		//- Get the boundary surfaces
		[[nodiscard]] Sptrvector<Surface>& boundaryRef() noexcept;


	// Member operators

		//- Disallow copy assignment
		Volume& operator=(const Volume&) = delete;

		//- Disallow move assignment
		Volume& operator=(Volume&&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
