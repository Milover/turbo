/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::Underlying

Description
	A helper class for implementing CRTP properly

\*---------------------------------------------------------------------------*/

#ifndef TURBO_UNDERLYING_H
#define TURBO_UNDERLYING_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

/*---------------------------------------------------------------------------*\
						Class Underlying Definition
\*---------------------------------------------------------------------------*/

template<typename T>
class Underlying
{
protected:

	// Constructors

		// Default constructor
		Underlying() = default;


public:

	// Constructors

		// Copy constructor
		Underlying(const Underlying&) = default;

		// Move constructor
		Underlying(Underlying&&) = default;


	// Destructor
	virtual ~Underlying() = default;


	// Member functions

		// Return reference to underlying type
		T& cast() noexcept;

		// Return const reference to underlying type
		const T& cast() const noexcept;


	// Member operators

		// Copy assignment
		Underlying& operator=(const Underlying&) = default;

		// Move assignment
		Underlying& operator=(Underlying&&) = default;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T>
T& Underlying<T>::cast() noexcept
{
	return static_cast<T&>(*this);
}

template<typename T>
const T& Underlying<T>::cast() const noexcept
{
	return static_cast<const T&>(*this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
