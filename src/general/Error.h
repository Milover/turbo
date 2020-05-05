/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Error functions and macros

\*---------------------------------------------------------------------------*/

#ifndef ERROR_H
#define ERROR_H

#include <cstdlib>
#include <iostream>
#include <utility>
#include <tuple>
#include <sstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * Constants * * * * * * * * * * * * * * * * * * //

#ifdef NDEBUG

	// debugging disabled
	static constexpr bool ndebug {true};

#else

	// debugging enabled
	static constexpr bool ndebug {false};

#endif


static constexpr char boldOn[] {"\033[1m"};

static constexpr char redBoldOn[] {"\033[1;31m"};

static constexpr char boldOff[] {"\033[0m"};

// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

//- Construct a string formatted bold red
template<typename... T>
constexpr std::string redBold(T&&... t)
{
	std::stringstream ss;

	ss << redBoldOn;
	(ss << ... << t);
	ss << boldOff;

	return ss.str();
}


//- Construct a string formatted bold
template<typename... T>
constexpr std::string bold(T&&... t)
{
	std::stringstream ss;

	ss << boldOn;
	(ss << ... << t);
	ss << boldOff;

	return ss.str();
}


//- Cleanup and exit with failure code and print an error message.
//	The first argument should be the FUNC_INFO macro, the 'message' can be
//	composed from any printable types
template<typename... T>
[[noreturn]] void error
(
	std::tuple<std::string, std::string, long>&& func_info,
	T&&... message
)
{
	auto func {std::move(std::get<0>(func_info))};
	auto file {std::move(std::get<1>(func_info))};
	auto line {std::move(std::get<2>(func_info))};

	std::string error
	{
		bold(file, ": ")
	  + "In function "
	  + bold("'", func, "':\n", file, ":", line, ": ")
	  + redBold("error: ")
	};

	if constexpr (ndebug)
	{
		std::cerr << error;
		(std::cerr << ... << std::forward<T>(message)) << '\n';
		std::exit(EXIT_FAILURE);
	}
	else
	{
		std::stringstream ss;

		ss << error;
		(ss << ... << std::forward<T>(message)) << '\n';

		throw std::runtime_error(ss.str());
	}
}


// * * * * * * * * * * * * * * Macros  * * * * * * * * * * * * * * * * * * * //

//- A macro which constructs a tuple containing the current function, source
//	file and line information
#define FUNC_INFO \
		std::forward_as_tuple(__PRETTY_FUNCTION__, __FILE__, __LINE__)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
