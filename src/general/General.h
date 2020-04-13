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
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * * Typedefs  * * * * * * * * * * * * * * * * * //

using Integer = int;


using Float = double;


using String = std::string;


template<typename T, typename U = T>
using Pair = std::pair<T, U>;


template<typename T>
using Uptr = std::unique_ptr<T>;


template<typename T>
using Vectorpair = std::vector<Pair<T>>;


template<typename T>
using Ptrvector = std::vector<Uptr<T>>;


template<typename T = String>
using Stringmap = std::map<String, T>;


template<typename T>
using Map = std::map<String, T>;


template<typename T>
using HashMap = std::unordered_map<String, T>;


// * * * * * * * * * * * * * * * Type Traits * * * * * * * * * * * * * * * * //

template<typename T>
using removeCVRef_t = std::remove_cv_t<std::remove_reference_t<T>>;


// * * * * * * * * * * * * * * * * Flags * * * * * * * * * * * * * * * * * * //

//- A dummy base for recursion flags
struct RecursionFlag {};


//- A dummy class to flag recursive actions in templates
struct Recurse : RecursionFlag {};


//- A dummy class to flag non-recursive actions in templates
struct NoRecurse : RecursionFlag {};



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
