/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::List

Description
	List class.

	NOTE: input parsing provisionally tested, godspeed

\*---------------------------------------------------------------------------*/

#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <type_traits>
#include <istream>
#include <ostream>
#include <sstream>

#include "Error.h"
#include "General.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// Forward declarations
template<typename T>
class List;

// * * * * * * * * * * * * * * * Type Traits * * * * * * * * * * * * * * * * //

//- Check if a type is a List
template<typename T, typename Value = void>
struct isList : std::false_type {};

template<typename T>
struct isList<T, std::void_t<typename removeCVRef_t<T>::value_type>>
:
	std::bool_constant
	<
		std::is_same_v
		<
			List<typename removeCVRef_t<T>::value_type>,
			removeCVRef_t<T>
		>
	>
{};

template<typename T>
inline constexpr bool isList_v = isList<T>::value;


/*---------------------------------------------------------------------------*\
						Class List Definition
\*---------------------------------------------------------------------------*/

template<typename T>
class List
{
public:

	using value_type		= T;
	using container_type	= std::vector<T>;
	using size_type			= typename container_type::size_type;
	using iterator			= typename container_type::iterator;
	using const_iterator	= typename container_type::const_iterator;
	using reference			= typename container_type::reference;
	using const_reference	= typename container_type::const_reference;

private:

	// Private data

		container_type data_;


public:

	// Constructors

		//- Default constructor
		List() = default;

		//- Construct from data
		template
		<
			typename... U,
			typename = std::enable_if_t
			<
				(std::is_same_v<T, removeCVRef_t<U>> && ...)
			>
		>
		List(U&&... u);

		//- Construct from data
		//	NOTE: could also just request something iterable
		template
		<
			typename U,
			typename = std::enable_if_t
			<
				std::is_same_v<container_type, removeCVRef_t<U>>
			>
		>
		explicit List(U&& u);

		//- Copy constructor
		List(const List&) = default;

		//- Move constructor
		List(List&&) = default;


	// Destructor
	~List() = default;


	// Member functions

		//- Append data
		template<typename... U>
		void append(U&&... u);

		//- Append data
		//	NOTE: could also just request something iterable
		template
		<
			typename U,
			typename = std::enable_if_t
			<
				std::is_same_v<container_type, removeCVRef_t<U>>
			 || std::is_same_v<List<T>, removeCVRef_t<U>>
			>
		>
		void append(U&& u);

		//- Get reference to last element
		[[nodiscard]] const_reference back() const;

		//- Get reference to last element
		[[nodiscard]] reference back();

		//- Get iterator to beginning
		[[nodiscard]] const_iterator begin() const noexcept;

		//- Get iterator to beginning
		[[nodiscard]] iterator begin() noexcept;

		//- Clear
		void clear() noexcept;

		//- Check if empty
		[[nodiscard]] bool empty() const noexcept;

		//- Get iterator to end
		[[nodiscard]] const_iterator end() const noexcept;

		//- Get iterator to end
		[[nodiscard]] iterator end() noexcept;

		//- Get reference to first element
		[[nodiscard]] const_reference front() const;

		//- Get reference to first element
		[[nodiscard]] reference front();

		//- Get data
		[[nodiscard]] const container_type& get() const noexcept;

		//- Get data
		[[nodiscard]] container_type& get() noexcept;

		//- Get size
		[[nodiscard]] size_type size() const noexcept;


	// Member operators

		//- Access operator
		[[nodiscard]] const_reference operator[](size_type pos) const;

		//- Access operator
		[[nodiscard]] reference operator[](size_type pos);

		//- Copy assignment operator
		List& operator=(const List&) = default;

		//- Move assignment operator
		List& operator=(List&&) = default;

		//- Equality operator
		[[nodiscard]] bool operator==(const List& l) const noexcept;

};

// * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * * //

//- Input stream output operator, appends to List
template
<
	typename T,
	typename = std::enable_if_t<std::is_default_constructible_v<T>>
>
std::istream& operator>>(std::istream& is, List<T>& l)
{
	// NOTE: we should implement this at some point
	static_assert(!std::is_same_v<String, T>);

	char c = is.get();

	// eat whitespace while looking for a '('
	while (c != '(')
	{
		if (!std::iswspace(c))
			error(FUNC_INFO, "expected '(' but found '", c, "'");
		else if (is.eof())
			error(FUNC_INFO, "could not find '(' before eof");
		else if (is.fail())
			error(FUNC_INFO, "input error");

		is.get(c);
	}

	while (is.peek() != ')')
	{
		if (is.eof())
			error(FUNC_INFO, "could not find ')' before eof");
		else if (is.fail())
			error(FUNC_INFO, "input error");

		// strings are (will be) read differently
		if constexpr (std::is_same_v<String, T>)
		{
			error(FUNC_INFO, "string parsing not implemented");
		}
		else
		{
			T t;
			is >> t;

			if (!is)
				error(FUNC_INFO, "input error");

			l.append(std::move(t));
		}
	}
	// extract the ')'
	c = is.get();

	return is;
}


//- Output stream input operator
template<typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& l)
{
	// so we don't mess up any formatting
	std::stringstream ss;

	ss << "(";
	for (auto& item : l.get())
	{
		ss << item;

		if (&item != &l.get().back())
			ss << " ";
	}
	ss << ")";

	os << ss.str();

	return os;
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename T>
template<typename... U, typename>
List<T>::List(U&&... u)
{
	this->append(std::forward<U>(u)...);
}


template<typename T>
template<typename U, typename>
List<T>::List(U&& u)
:
	data_ {std::forward<U>(u)}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T>
template<typename... U>
void List<T>::append(U&&... u)
{
	// no need to reserve for single input
	if constexpr (sizeof...(u) > 1)
	{
		this->data_.reserve(sizeof...(u) + this->data_.size());
	}

	(this->data_.emplace_back(std::forward<U>(u)), ...);
}


template<typename T>
template<typename U, typename>
void List<T>::append(U&& u)
{
	if constexpr (std::is_same_v<List<T>, removeCVRef_t<U>>)
	{
		this->data_.insert
		(
			this->data_.end(),
			u.data_.begin(),
			u.data_.end()
		);
	}
	else
	{
		this->data_.insert
		(
			this->data_.end(),
			u.begin(),
			u.end()
		);
	}
}


template<typename T>
typename List<T>::const_reference List<T>::back() const
{
	return this->data_.back();
}


template<typename T>
typename List<T>::reference List<T>::back()
{
	return this->data_.back();
}


template<typename T>
typename List<T>::const_iterator List<T>::begin() const noexcept
{
	return this->data_.begin();
}


template<typename T>
typename List<T>::iterator List<T>::begin() noexcept
{
	return this->data_.begin();
}


template<typename T>
void List<T>::clear() noexcept
{
	this->data_.clear();
}


template<typename T>
bool List<T>::empty() const noexcept
{
	return this->data_.empty();
}


template<typename T>
typename List<T>::const_iterator List<T>::end() const noexcept
{
	return this->data_.end();
}


template<typename T>
typename List<T>::iterator List<T>::end() noexcept
{
	return this->data_.end();
}


template<typename T>
typename List<T>::const_reference List<T>::front() const
{
	return this->data_.front();
}


template<typename T>
typename List<T>::reference List<T>::front()
{
	return this->data_.front();
}


template<typename T>
const typename List<T>::container_type& List<T>::get() const noexcept
{
	return this->data_;
}


template<typename T>
typename List<T>::container_type& List<T>::get() noexcept
{
	return this->data_;
}


template<typename T>
typename List<T>::size_type List<T>::size() const noexcept
{
	return this->data_.size();
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename T>
typename List<T>::const_reference List<T>::operator[](size_type pos) const
{
	return this->data_[pos];
}


template<typename T>
typename List<T>::reference List<T>::operator[](size_type pos)
{
	return this->data_[pos];
}


template<typename T>
bool List<T>::operator==(const List<T>& l) const noexcept
{
	if constexpr (std::is_floating_point_v<T>)
	{
		return std::equal
		(
			this->data_.begin(),
			this->data_.end(),
			l.data_.begin(),
			[](const auto& t1, const auto& t2) -> bool
			{
				return isEqual(t1, t2);
			}
		);
	}
	else
		return std::equal
		(
			this->data_.begin(),
			this->data_.end(),
			l.data_.begin()
		);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
