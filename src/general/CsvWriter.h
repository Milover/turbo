/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::CsvWriter

Description
	A simple class for writing stuff to .csv files

SourceFiles
	CsvWriter.cpp

\*---------------------------------------------------------------------------*/

#ifndef TURBO_CSV_WRITER_H
#define TURBO_CSV_WRITER_H

#include <fstream>
#include <utility>

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

/*---------------------------------------------------------------------------*\
						Class CsvWriter Declaration
\*---------------------------------------------------------------------------*/

class CsvWriter
{
private:

	// Private data

		Path file_;
		std::ofstream stream_;


public:

	// Public data

		char delimiter {'\t'};
		char comment {'#'};


	// Constructors

		//- Construct from a file path and mode and precision,
		//	NOTE: throws when failbit is set
		CsvWriter
		(
			const Path& file,
			std::ios::openmode mode = std::ios::out,
			Integer precision = 9
		);


	// Member functions

		//- Modify state flags
		void clear(std::ios::iostate state = std::ios::goodbit);

		//- Get output file
		[[nodiscard]] Path file() const;

		//- Synchronize with underlying output device
		void flush();

		//- Set output file
		void setFile
		(
			const Path& file,
			std::ios::openmode mode = std::ios::out,
			Integer precision = 9
		);

		//- Write data line
		template<typename... Ts>
		void write(Ts&&... ts);

		//- Write comment line
		template<typename... Ts>
		void writeComment(Ts&&... ts);

		//- Write header line
		template<typename... Ts>
		void writeHeader(Ts&&... ts);


	// Member operators

		//- Output operator
		template<typename T>
		CsvWriter& operator<<(T&& t);

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename... Ts>
void CsvWriter::write(Ts&&... ts)
{
	auto output = [&]
	(
		auto self [[maybe_unused]],
		auto&& u,
		auto&&... us
	) -> void
	{
		if constexpr (sizeof...(us) != 0)
		{
			stream_ << u << delimiter;


			self(self, std::forward<decltype(us)>(us)...);
		}
		else
			stream_ << u << '\n';
	};

	output(output, std::forward<Ts>(ts)...);
}


template<typename... Ts>
void CsvWriter::writeComment(Ts&&... ts)
{
	stream_ << comment << ' ';

	(stream_ << ... << std::forward<Ts>(ts)) << '\n';
}


template<typename... Ts>
void CsvWriter::writeHeader(Ts&&... ts)
{
	stream_ << comment << ' ';

	write(std::forward<Ts>(ts)...);
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename T>
CsvWriter& CsvWriter::operator<<(T&& t)
{
	stream_ << std::forward<T>(t);

	return *this;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
