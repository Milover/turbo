/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Translate

Description
	Translate class for translation of geometry

SourceFiles
	Translate.cpp

\*---------------------------------------------------------------------------*/

#ifndef TRANSLATE_BASE_H
#define TRANSLATE_BASE_H

#include <memory>

#include "ManipulatorBase.h"
#include "Point.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Translate Declaration
\*---------------------------------------------------------------------------*/

class Translate final
:
	public ManipulatorBase<Vector>
{
private:

	// Private data

		std::unique_ptr<Vector> vector_;


protected:

	// Member functions

		//- Manipulate geometry
		void executeManipulation
		(
			const Vectorpair<int>& dimTags
		) const override;


public:

	// Constructors

		//- Default constructor
		Translate() = default;


	//- Destructor
	~Translate() = default;


	// Member functions

		//- Set translation vector
		void setParameters(const Vector& vector) noexcept override;

		//- Set translation vector from points,
		//  'pTo' defaults to origin
		void setParameters
		(
			const Point& pFrom,
			const Point& pTo = Point {0.0, 0.0}
		) noexcept;

		//- Check if translation vector is set
		bool isSet() const noexcept override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
