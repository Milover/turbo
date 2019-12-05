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
#include <string>
#include <type_traits>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * Constants * * * * * * * * * * * * * * * * * * //

static const std::string boldOn {"\e[1m"};


static const std::string redBoldOn {"\e[1;31m"};


static const std::string boldOff {"\e[0m"};


// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

//- Construct error message
inline std::string errorMessage
(
	const std::string& function,
	const std::string& file,
	const long line,
	const std::string& message
)
{
	std::string error
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
throwError(const std::string& message)
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


#define THROW_RUNTIME_ERROR(message) \
	throwError<std::runtime_error> \
		(errorMessage(__PRETTY_FUNCTION__, __FILE__, __LINE__, (message)))


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
