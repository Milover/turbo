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

#include <stdexcept>
#include <type_traits>

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * Constants * * * * * * * * * * * * * * * * * * //

static const String boldOn {"\033[1m"};


static const String redBoldOn {"\033[1;31m"};


static const String boldOff {"\033[0m"};


// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

//- Construct error message
inline String errorMessage
(
	const String& function,
	const String& file,
	const long line,
	const String& message
)
{
	String error
	{
		boldOn +
		file + ": " +
		boldOff +
		"In function " +
		boldOn +
		"'" + function + "':\n" +
		file + ":" +
		std::to_string(line) + ": " +
		boldOff +
		redBoldOn +
		"error: " +
		boldOff +
		message +
		"\n"
	};

	return error;
}


//- Throw an error
template<typename T>
[[noreturn]] std::enable_if_t<
	std::is_base_of_v<std::runtime_error, T> ||
	std::is_base_of_v<std::logic_error, T>
>
throwError(const String& message)
{
	throw T(message);
}


// * * * * * * * * * * * * * * Macros  * * * * * * * * * * * * * * * * * * * //

#define THROW_ARGUMENT_ERROR(message) \
	throwError<std::invalid_argument> \
		(errorMessage(__PRETTY_FUNCTION__, __FILE__, __LINE__, (message)))


#define THROW_DOMAIN_ERROR(message) \
	throwError<std::domain_error> \
		(errorMessage(__PRETTY_FUNCTION__, __FILE__, __LINE__, (message)))


#define THROW_LOGIC_ERROR(message) \
	throwError<std::logic_error> \
		(errorMessage(__PRETTY_FUNCTION__, __FILE__, __LINE__, (message)))


#define THROW_RANGE_ERROR(message) \
	throwError<std::out_of_range> \
		(errorMessage(__PRETTY_FUNCTION__, __FILE__, __LINE__, (message)))


#define THROW_RUNTIME_ERROR(message) \
	throwError<std::runtime_error> \
		(errorMessage(__PRETTY_FUNCTION__, __FILE__, __LINE__, (message)))


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
