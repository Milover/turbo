/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::ProfileGeneratorBase

Description
	Abstract base class for profle generator classes

\*---------------------------------------------------------------------------*/

#ifndef PROFILE_GENERATOR_H
#define PROFILE_GENERATOR_H

#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class ProfileGeneratorBase Declaration
\*---------------------------------------------------------------------------*/

class ProfileGeneratorBase
{
protected:

	// Protected data

		Vectorpair<double> xyUpper_;
		Vectorpair<double> xyLower_;


	// Constructors
		
		//- Default constructor
		ProfileGeneratorBase() = default;
	

	// Member functions

		//- Parse input data
		virtual void parseInput(const Stringmap& input) = 0;


public:
	
	// Constructors
		
		//- Copy constructor
		ProfileGeneratorBase(const ProfileGeneratorBase&) = default;


	//- Destructor
	virtual ~ProfileGeneratorBase() = default;


	// Member functions
	
		//- Generate profile coordinates
		virtual void generate() = 0;

		//- Get number of (camber line) points
		inline int getSize() const noexcept
		{
			return xyUpper_.size();
		}

		//- Check if coordinates have beed generated
		inline bool isEmpty() const noexcept
		{
			return xyUpper_.empty() && xyLower_.empty();
		}

		//- Get upper point at ``pos''
		inline auto getUpperAt(const int pos) const
		{
			return xyUpper_.at(pos);
		}

		//- Get lower point at ``pos''
		inline auto getLowerAt(const int pos) const
		{
			return xyLower_.at(pos);
		}


	// Member operators
		
		//- Disallow assignment
		ProfileGeneratorBase& operator=(const ProfileGeneratorBase&) = delete;


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
