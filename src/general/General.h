/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	General use alias templates

\*---------------------------------------------------------------------------*/

#ifndef GENERAL_H
#define GENERAL_H

#include <array>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using Integer = int;


using Float = double;


using Word = std::string;


using PointCoordinates = std::array<Float, 3>;


template<typename T>
using Uptr = std::unique_ptr<T>;


template<typename T>
using Vectorpair = std::vector<std::pair<T, T>>;


template<typename T>
using Ptrvector = std::vector<Uptr<T>>;


template<typename T = Word>
using Stringmap = std::map<Word, T>;


template<typename T>
using Map = std::map<Word, T>;


template<typename T>
using HashMap = std::unordered_map<Word, T>;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
