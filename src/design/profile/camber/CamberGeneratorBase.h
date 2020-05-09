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

#include "Error.h"
#include "General.h"
#include "Registry.h"
#include "Variables.h"
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

	using Spacing = input::CamberPointSpacing::Type;


	// Private data

		input::NumberOfCamberPoints nPoints_;
		input::CamberPointSpacing spacing_;

		Float increment_;


	// Member functions

		//- Compute next point on abscissa
		Float computeX(const Integer count) const noexcept;


protected:

	using Point = Vector;

	// Protected data

		const input::CamberAngle camber_;


	// Constructors

		//- Construct from a registry
		explicit CamberGeneratorBase(const input::Registry& reg);


	// Member functions

		//- Compute camber ordinate at a 'x'
		virtual Float computeY(const Float x) const = 0;


public:

	// Constructors

		//- Copy constructor
		CamberGeneratorBase(const CamberGeneratorBase&) = delete;

		//- Move constructor
		CamberGeneratorBase(CamberGeneratorBase&&) = default;


	//- Destructor
	virtual ~CamberGeneratorBase() = default;


	// Member functions

		//- Generate camber line
		std::vector<Point> generate() const noexcept;

		//- Get inclination angle at 'x' in radians
		virtual Float inclination(const Float x) const noexcept(ndebug) = 0;


	// Member operators

		//- Copy assignment operator
		CamberGeneratorBase& operator=
		(
			const CamberGeneratorBase&
		) = delete;

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
