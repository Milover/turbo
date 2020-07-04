/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <fstream>
#include <iomanip>

#include "CsvWriter.h"

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

CsvWriter::CsvWriter
(
	const Path& file,
	std::ios::openmode mode,
	Integer precision
)
:
	file_ {file},
	stream_ {file, mode}
{
	stream_.exceptions(std::ofstream::failbit);

	stream_ << std::fixed << std::setprecision(precision);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void CsvWriter::clear(std::ios::iostate state)
{
	stream_.clear(state);
}


Path CsvWriter::file() const
{
	return file_;
}


void CsvWriter::flush()
{
	stream_.flush();
}


void CsvWriter::setFile
(
	const Path& file,
	std::ios::openmode mode,
	Integer precision
)
{
	stream_ = std::ofstream {file, mode};

	stream_.exceptions(std::ofstream::failbit);

	stream_ << std::fixed << std::setprecision(precision);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// ************************************************************************* //
