/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::CsvReader

Description
	CsvReader class

SourceFiles
	CsvReader.cpp

\*---------------------------------------------------------------------------*/

#ifndef TURBO_INPUT_CSV_READER_H
#define TURBO_INPUT_CSV_READER_H

#include <filesystem>
#include <fstream>
#include <istream>
#include <sstream>
#include <tuple>
#include <type_traits>
#include <utility>

#include "Error.h"
#include "General.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class CsvReader Definition
\*---------------------------------------------------------------------------*/

template<typename... Fields>
class CsvReader
{
private:

	static_assert(sizeof...(Fields) > 0);
	// FIXME: should require operator>> to be defined for each Field

	// Private data

		std::tuple<std::vector<Fields>...> fields_;


	// Member functions

		//- Read a line and store the values
		template<std::size_t... Is>
		void readLine
		(
			std::stringstream& ss,
			std::size_t lineCount,
			std::index_sequence<Is...>
		);

public:

	// Public data

		const char delimiter;
		const char comment;


	// Constructors

		//- Construct from delimiter and comment chars
		CsvReader
		(
			const char delim = '\t',
			const char comm = '#'
		);

		//- Copy constructor
		CsvReader(const CsvReader&) = default;

		//- Move constructor
		CsvReader(CsvReader&&) = default;


	//- Destructor
	~CsvReader() = default;


	// Member functions

		//- Clear fields
		void clear();

		//- Get a const reference to a column
		template<std::size_t Id>
		const auto& cref() const;

		//- Read a file
		void read(const Path& file);

		//- Read a from an istream
		void read(std::istream& is);

		//- Get a reference to a column
		template<std::size_t Id>
		auto& ref();


	// Member operators

		//- Copy assignment operator
		CsvReader& operator=(const CsvReader&) = default;

		//- Move assignment operator
		CsvReader& operator=(CsvReader&&) = default;

};


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<typename... Fields>
template<std::size_t... Is>
void CsvReader<Fields...>::readLine
(
	std::stringstream& ss,
	std::size_t lineCount,
	std::index_sequence<Is...>
)
{
	auto val = [&](auto& thing) -> void
	{
		using Thing = typename removeCVRef_t<decltype(thing)>::value_type;

		Thing t;

		if constexpr (std::is_same_v<String, Thing>)
		{
			t = readString(ss);
		}
		else
		{
			ss >> t;
		}

		thing.emplace_back(std::move(t));
	};
	auto delimVal = [&](auto& thing, const char delim) -> void
	{
		while (ss)
		{
			char c;
			ss.get(c);

			if (c == delim)
				break;
			else if (!std::iswspace(c))
				error
				(
					FUNC_INFO,
					"CsvReader error on line: ", lineCount,
					" expected '", delim, "' but found '", c, "'"
				);
			else if (ss.fail())
				error
				(
					FUNC_INFO,
					"CsvReader error on line: ", lineCount
				);
		}

		val(thing);
	};

	(
		(
			Is == 0
		  ? val(std::get<Is>(this->fields_))
		  : delimVal(std::get<Is>(this->fields_), this->delimiter)
		),
		...
	);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename... Fields>
CsvReader<Fields...>::CsvReader
(
	const char delim,
	const char comm
)
:
	//fields_ {{}...},
	delimiter {delim},
	comment {comm}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename... Fields>
void CsvReader<Fields...>::clear()
{
	auto clr = [](auto&&... args) -> void
	{
		(args.clear(), ...);
	};

	return std::apply(clr, this->fields_);
}


template<typename... Fields>
template<std::size_t Id>
const auto& CsvReader<Fields...>::cref() const
{
	static_assert(Id >= 0);
	static_assert(Id < sizeof...(Fields));

	return std::get<Id>(this->fields_);
}


template<typename... Fields>
void CsvReader<Fields...>::read(const Path& file)
{
	if(!std::filesystem::exists(file))
		error(FUNC_INFO, "file: ", file, " doesn't exist");
	else if (!std::filesystem::is_regular_file(file))
		error(FUNC_INFO, "file: ", file, " not a regular file");

	std::ifstream ifs {file};

	this->read(ifs);
}


template<typename... Fields>
void CsvReader<Fields...>::read(std::istream& is)
{
	String s;
	std::size_t count {0};
	while (is)
	{
		std::getline(is, s);

		if (s.empty())
			continue;

		std::stringstream ss;
		ss << s;

		if (ss.peek() == this->comment)
			continue;

		this->readLine
		(
			ss,
			count,
			std::index_sequence_for<Fields...> {}
		);

		if (is.fail())
			error(FUNC_INFO, "CsvReader error");
		else if (ss.fail())
			error
			(
				FUNC_INFO,
				"CsvReader error on line: ", count
			);

		++count;
	}
}


template<typename... Fields>
template<std::size_t Id>
auto& CsvReader<Fields...>::ref()
{
	static_assert(Id >= 0);
	static_assert(Id < sizeof...(Fields));

	return std::get<Id>(this->fields_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
