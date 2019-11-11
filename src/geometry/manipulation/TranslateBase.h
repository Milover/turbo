/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::TranslateBase

Description
	Base class template for geometry translation operations.

SourceFiles
	TranslateBase.cpp

\*---------------------------------------------------------------------------*/

#ifndef TRANSLATE_BASE_H
#define TRANSLATE_BASE_H

#include <memory>

#include "ManipulatorBase.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class TranslateBase Declaration
\*---------------------------------------------------------------------------*/

template<typename... T>
class TranslateBase
:
	public ManipulatorBase<T...>
{
private:

	// Private data

		std::unique_ptr<Vector> vector_;

protected:

	// Member functions

		//- Set vector
		void setVector(const Vector& vector) noexcept;


public:

	// Constructors

		//- Default constructor
		TranslateBase() = default;

		//- Disallow copy construction
		TranslateBase(const TranslateBase&) = delete;


	//- Destructor
	virtual ~TranslateBase();


	// Member functions

		//- Manipulate geometry
		void manipulate(const Vectorpair<int>& dimTags) const final;

		//- Check if translation vector is set
		bool isSet() const noexcept final;

		//- Set translation vector
		virtual void setParameters(const T&... t) noexcept = 0;


	// Member operators

		//- Disallow assignment
		TranslateBase& operator=(const TranslateBase&) = delete;


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
