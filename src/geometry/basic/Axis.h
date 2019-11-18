/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Axis

Description
	Axis base class and derived classes for ease of use

SourceFiles
	Axis.cpp

\*---------------------------------------------------------------------------*/

#ifndef AXIS_H
#define AXIS_H

#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Axis Declaration
\*---------------------------------------------------------------------------*/

class Axis
{
private:

	// Protected data
	
		PointCoordinates point_;
		Vector vector_;


public:

	// Public data
	inline static constexpr int X = 0;
	inline static constexpr int Y = 1;
	inline static constexpr int Z = 2;


	// Constructors

		//- Construct from components
		Axis
		(
			double x,
			double y,
			double z,
			const Vector& vector
		) noexcept;

		//- Copy constructor
		Axis(const Axis&) noexcept;


	//- Destructor
	virtual ~Axis() = default;


	// Member functions

		//- Get point
		PointCoordinates getPointCoordinates() const noexcept;

		//- Get vector
		Vector getVector() const noexcept;


	// Member operators

		//- Equal to operator
		bool operator==(const Axis&) const;

		//- Not equal to operator
		bool operator!=(const Axis&) const;

		//- Disallow assignment
		Axis& operator=(const Axis&) = delete;

};


/*---------------------------------------------------------------------------*\
						Class XAxis Definition
\*---------------------------------------------------------------------------*/

class XAxis final
:
	public Axis
{
public:

	// Constructors

		//- Construct from components
		XAxis() noexcept
		:
			Axis
			{
				0, 0, 0,
				Vector {1, 0, 0}
			}
		{}

		//- Copy constructor
		XAxis(const XAxis&) = default;


	//- Destructor
	~XAxis() = default;

};


/*---------------------------------------------------------------------------*\
						Class YAxis Definition
\*---------------------------------------------------------------------------*/

class YAxis final
:
	public Axis
{
public:

	// Constructors

		//- Construct from components
		YAxis() noexcept
		:
			Axis
			{
				0, 0, 0,
				Vector {0, 1, 0}
			}
		{}

		//- Copy constructor
		YAxis(const YAxis&) = default;


	//- Destructor
	~YAxis() = default;

};


/*---------------------------------------------------------------------------*\
						Class ZAxis Definition
\*---------------------------------------------------------------------------*/

class ZAxis final
:
	public Axis
{
public:

	// Constructors

		//- Construct from components
		ZAxis() noexcept
		:
			Axis
			{
				0, 0, 0,
				Vector {0, 0, 1}
			}
		{}

		//- Copy constructor
		ZAxis(const ZAxis&) = default;


	//- Destructor
	~ZAxis() = default;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
