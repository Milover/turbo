/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::CorrectedValue

Description
	Class CorrectedValue.

	A CRTP class to allow registry objects to track their progress through the
	design procedure.

	FIXME: should handle types other than floats

\*---------------------------------------------------------------------------*/

#ifndef INPUT_CORRECTED_VALUE_H
#define INPUT_CORRECTED_VALUE_H

#include <cmath>
#include <type_traits>

#include "General.h"
#include "Underlying.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class CorrectedValue Definition
\*---------------------------------------------------------------------------*/

template<typename Correction, typename RegObj>
class CorrectedValue
:
	public Underlying<RegObj>
{
private:

	friend RegObj;
	using CVBase = CorrectedValue<Correction, RegObj>;

	static_assert(std::is_floating_point_v<Correction>);


	// Constructors

		//- Default constructor
		CorrectedValue() = default;


protected:

	// Protected data

		Correction correction_ {0.0};
		Correction totalCorrection_ {0.0};

		bool checkpoint_ {false};
		Correction valueCp_ {0.0};
		Correction correctionCp_ {0.0};
		Correction totalCorrectionCp_ {0.0};


public:

	// Constructors

		//- Copy constructor
		CorrectedValue(const CorrectedValue&) = default;

		//- Move constructor
		CorrectedValue(CorrectedValue&&) = default;

	//- Destructor
	virtual ~CorrectedValue() = default;


	// Member functions

		//- clear checkpoint
		void clearCheckpoint() noexcept;

		//- Add correction
		void correct(const Correction& corr);

		//- Get last correction
		[[nodiscard]] Correction correction() const noexcept;

		//- Get old value
		[[nodiscard]] Correction oldValue() const noexcept;

		//- Restore from checkpoint
		bool restore() noexcept;

		//- Revert to previous state (value and total correction)
		//	FIXME: should handle things other than floats
		void revert();

		//- Set checkpoint
		void setCheckpoint() noexcept;

		//- Check if tolerance is satisfied (correction_ <= tol)
		[[nodiscard]] bool tolerance(const Correction& tol) const noexcept;

		//- Get total correction
		[[nodiscard]] Correction totalCorrection() const noexcept;


	// Member operators

		//- Copy assignment operator
		CorrectedValue& operator=(const CorrectedValue&) = default;

		//- Move assignment operator
		CorrectedValue& operator=(CorrectedValue&&) = default;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename Correction, typename RegObj>
void CorrectedValue<Correction, RegObj>::clearCheckpoint() noexcept
{
	this->checkpoint_ = false;
	this->valueCp_ = 0.0;
	this->correctionCp_ = 0.0;
	this->totalCorrectionCp_ = 0.0;
}


template<typename Correction, typename RegObj>
void CorrectedValue<Correction, RegObj>::correct(const Correction& corr)
{
	this->correction_ = corr;

	this->totalCorrection_ += corr;
	this->cast().set(this->cast().value() + corr);
}


template<typename Correction, typename RegObj>
Correction CorrectedValue<Correction, RegObj>::correction() const noexcept
{
	return this->correction_;
}


template<typename Correction, typename RegObj>
Correction CorrectedValue<Correction, RegObj>::oldValue() const noexcept
{
	return this->cast().value() - this->correction_;
}


template<typename Correction, typename RegObj>
bool CorrectedValue<Correction, RegObj>::restore() noexcept
{
	if (this->checkpoint_)
	{
		this->cast().set(this->valueCp_);
		this->correction_ = this->correctionCp_;
		this->totalCorrection_ = this->totalCorrectionCp_;
	}

	return this->checkpoint_;
}


template<typename Correction, typename RegObj>
void CorrectedValue<Correction, RegObj>::revert()
{
	if (isEqual(this->correction_, 0.0))
		return;

	this->totalCorrection_ -= this->correction_;
	this->cast().set(this->cast().value() - this->correction_);

	this->correction_ = 0.0;
}


template<typename Correction, typename RegObj>
void CorrectedValue<Correction, RegObj>::setCheckpoint() noexcept
{
	this->checkpoint_ = true;

	this->valueCp_ = this->cast().value();
	this->correctionCp_ = this->correction_;
	this->totalCorrectionCp_ = this->totalCorrection_;
}


template<typename Correction, typename RegObj>
bool CorrectedValue<Correction, RegObj>::
tolerance(const Correction& tol) const noexcept
{
	return isLessOrEqual(std::abs(this->correction_), tol);
}


template<typename Correction, typename RegObj>
Correction CorrectedValue<Correction, RegObj>::totalCorrection() const noexcept
{
	return this->totalCorrection_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
