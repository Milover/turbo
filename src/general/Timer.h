/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::Timer

Description
	A simple timer class.

\*---------------------------------------------------------------------------*/

#ifndef TURBO_TIMER_H
#define TURBO_TIMER_H

#include <chrono>

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

/*---------------------------------------------------------------------------*\
						Class Timer Declaration
\*---------------------------------------------------------------------------*/

class Timer
{
private:

	// Private data

		std::chrono::time_point<std::chrono::system_clock> start_;
		std::chrono::time_point<std::chrono::system_clock> end_;
		bool running_ {false};


public:

	using Seconds = std::chrono::seconds;
	using Milliseconds = std::chrono::milliseconds;

	// Member functions

		//- Start the timer
		void start();

		//- Stop the timer
		void stop();

		//- Get time from start to 'now' if running, or last interval
		template<typename T = Milliseconds>
		Float elapsed();

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T>
Float Timer::elapsed()
{
	std::chrono::time_point<std::chrono::system_clock> endTime;

	if(running_)
		endTime = std::chrono::system_clock::now();
	else
		endTime = end_;

	return std::chrono::duration_cast<T>(endTime - start_).count();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
