/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::ProfileGenerator

Description
	Class ProfileGenerator

SourceFiles
	ProfileGenerator.cpp

\*---------------------------------------------------------------------------*/

#ifndef PROFILE_GENERATOR_H
#define PROFILE_GENERATOR_H

#include <string>
#include <vector>

#include "CamberGeneratorBase.h"
#include "DistributionGeneratorBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
				Class ProfileGenerator Declaration
\*---------------------------------------------------------------------------*/

class ProfileGenerator
{
private:

	typedef std::vector<PointCoordinates>::iterator iterator;
	typedef std::vector<PointCoordinates>::const_iterator const_iterator;


	// Private data

		Stringmap<double> data_;

		std::unique_ptr<CamberGeneratorBase> camberGenerator_;
		std::unique_ptr<DistributionGeneratorBase> distributionGenerator_;

		std::vector<PointCoordinates> profile_;


	// Member functions

		//- Set camber type
		void initializeCamberGenerator(const Stringmap<>& input);

		//- Set distribution type
		void initializeDistributionGenerator(const Stringmap<>& input);

		//- Build profile from upper and lower surface points
		//  order of points is: upper TE - LE - lower TE
		void finalize(const Vectorpair<PointCoordinates>& profile) noexcept;

		//- Generate camber line
		void generateCamberLine(const double camberAngle) noexcept;

		//- Store key value to map
		void store
		(
			const std::string& key,
			const double value
		);


public:

	// Constructors

		//- Construct from input data
		ProfileGenerator(const Stringmap<>& input);

		//- Move constructor
		ProfileGenerator(ProfileGenerator&&) = default;


	//- Destructor
	~ProfileGenerator() = default;


	// Member functions

		//- Get iterator to beginning
		iterator begin();

		//- Get const iterator to beginning
		const_iterator begin() const;

		//- Check if coordinates have beed generated
		bool empty() const noexcept;

		//- Get iterator to end
		iterator end();

		//- Get const iterator to end
		const_iterator end() const;

		//- Generate profile
		void generate(const double camberAngle);

		//- Get value
		double get(const std::string& key) const;

		//- Check if value exists
		bool hasValue(const std::string& key) const noexcept;

		//- Get number of profile points
		int size() const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
