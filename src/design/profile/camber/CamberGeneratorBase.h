/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::CamberGeneratorBase

Description
	Abstract base class for camber generator classes

SourceFiles
	CamberGeneratorBase.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_CAMBER_GENERATOR_BASE_H
#define DESIGN_CAMBER_GENERATOR_BASE_H

#include <vector>

#include "General.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
					Class CamberGeneratorBase Declaration
\*---------------------------------------------------------------------------*/

class CamberGeneratorBase
{
private:

	// Private data

		enum class Spacing
		{
			LINEAR,
			COSINE
		};

		Integer camberPoints_ {200};
		Float increment_;
		Spacing spacing_ {Spacing::COSINE};


	// Member functions

		//- Compute next point on abscissa
		Float computeX(const Integer count) const noexcept;


protected:

	using Point = Vector;

	// Protected data

		const Float camber_;


	// Constructors

		//- Default constructor
		explicit CamberGeneratorBase(const Float camber);
			// TODO: clean up a bit


	// Member functions

		//- Compute camber ordinate at a 'x'
		virtual Float computeY(const Float x) const = 0;


public:

	// Constructors

		//- Copy constructor
		CamberGeneratorBase(const CamberGeneratorBase&) = default;

		//- Move constructor
		CamberGeneratorBase(CamberGeneratorBase&&) = default;


	//- Destructor
	virtual ~CamberGeneratorBase() = default;


	// Member functions

		//- Generate camber line
		std::vector<Point> generate() const noexcept;

		//- Get inclination angle at 'x' in radians
		virtual Float inclination(const Float x) const = 0;


	// Member operators

		//- Copy assignment operator
		CamberGeneratorBase& operator=
		(
			const CamberGeneratorBase&
		) = default;

		//- Move assignment operator
		CamberGeneratorBase& operator=
		(
			CamberGeneratorBase&&
		) = default;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
