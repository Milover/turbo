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

#ifndef CAMBER_GENERATOR_BASE_H
#define CAMBER_GENERATOR_BASE_H

#include <string>
#include <vector>

#include "InputObjectBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
					Class CamberGeneratorBase Declaration
\*---------------------------------------------------------------------------*/

class CamberGeneratorBase
:
	public InputObjectBase<double>
{
private:

	typedef std::vector<PointCoordinates>::iterator Iterator;
	typedef std::vector<PointCoordinates>::const_iterator Constiterator;


	// Private data

		enum class SpacingType
		{
			LINEAR,
			COSINE
		};

		double increment_;
		int camberPoints_ {100};
		SpacingType spacing_ {SpacingType::COSINE};

		std::vector<PointCoordinates> camber_;


	// Member functions

		//- Compute next point on abscissa
		double computeX(const double x) const noexcept;

		//- Parse number of points
		void parseCamberPoints(const std::string& value);

		//- Parse spacing type
		void parseSpacing(const std::string& value);

		//- Set spacing increment
		void setIncrement() noexcept;


protected:

	// Protected data

		const double chord_ {1.0};


	// Constructors

		//- Default constructor
		CamberGeneratorBase(const Stringmap<>& input);


	// Member functions

		//- Check values
		virtual void check() const;

		//- Compute camber parameters to satisfy
		//  a given camber angle
		virtual void computeParameters(const double camberAngle) = 0;

		//- Compute camber ordinate at a ``x''
		virtual double computeY(const double x) const = 0;

		//- Convert value to double
		double convert(const std::string& value) const final;

		//- Parse input
		virtual void parse(const Stringmap<>& input) override;


public:

	// Constructors

		//- Move constructor
		CamberGeneratorBase(CamberGeneratorBase&&) = default;


	//- Destructor
	virtual ~CamberGeneratorBase() = default;


	// Member functions

		//- Get iterator to beginning
		Iterator begin();

		//- Get const iterator to beginning
		Constiterator begin() const;

		//- Check if empty
		bool empty() const noexcept;

		//- Get iterator to end
		Iterator end();

		//- Get const iterator to end
		Constiterator end() const;

		//- Generate camber line
		void generate(const double camberAngle) noexcept;

		//- Get inlination angle at ``x''
		virtual double getInclinationAt(const double x) const = 0;

		//- Check if value is initialized
		bool hasValue(const std::string& key) const noexcept final;

		//- Get size
		int size() const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
