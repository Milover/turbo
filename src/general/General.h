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
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Debug.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * * Typedefs  * * * * * * * * * * * * * * * * * //

using Integer = int;


using Intvector = std::vector<Integer>;


using Float = double;


using Floatvector = std::vector<Float>;


using Path = std::filesystem::path;


using String = std::string;


template<typename T, typename U = T>
using Pair = std::pair<T, U>;


template<typename T>
using Uptr = std::unique_ptr<T>;


template<typename T>
using Sptr = std::shared_ptr<T>;


template<typename T>
using Wptr = std::weak_ptr<T>;


template<typename T, typename U = T>
using Vectorpair = std::vector<Pair<T, U>>;


template<typename T>
using Uptrvector = std::vector<Uptr<T>>;


template<typename T>
using Sptrvector = std::vector<Sptr<T>>;


template<typename T>
using Wptrvector = std::vector<Wptr<T>>;


template<typename T>
using Map = std::map<String, T>;


template<typename T>
using HashMap = std::unordered_map<String, T>;


// * * * * * * * * * * * * * * * Type Traits * * * * * * * * * * * * * * * * //

//- Remove const, volatile and reference from a type
template<typename T>
using removeCVRef_t = std::remove_cv_t<std::remove_reference_t<T>>;


//- Check if a type is a Uptr
template<typename T, typename Element = void>
struct isUptr : std::false_type {};

template<typename T>
struct isUptr<T, std::void_t<typename removeCVRef_t<T>::element_type>>
:
	std::bool_constant
	<
		std::is_same_v
		<
			Uptr<typename removeCVRef_t<T>::element_type>,
			removeCVRef_t<T>
		>
	>
{};

template<typename T>
inline constexpr bool isUptr_v = isUptr<T>::value;


//- Check if a type is a Sptr
template<typename T, typename = void>
struct isSptr : std::false_type {};

template<typename T>
struct isSptr<T, std::void_t<typename removeCVRef_t<T>::element_type>>
:
	std::bool_constant
	<
		std::is_same_v
		<
			Sptr<typename removeCVRef_t<T>::element_type>,
			removeCVRef_t<T>
		>
	>
{};

template<typename T>
inline constexpr bool isSptr_v = isSptr<T>::value;



//- Check if a type is a Wptr
template<typename T, typename Element = void>
struct isWptr : std::false_type {};

template<typename T>
struct isWptr<T, std::void_t<typename removeCVRef_t<T>::element_type>>
:
	std::bool_constant
	<
		std::is_same_v
		<
			Wptr<typename removeCVRef_t<T>::element_type>,
			removeCVRef_t<T>
		>
	>
{};

template<typename T>
inline constexpr bool isWptr_v = isWptr<T>::value;


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
