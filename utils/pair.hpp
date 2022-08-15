/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:30:25 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/15 14:30:34 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace ft
{
	template<class T1, class T2>
	struct pair
	{
		public:
			typedef T1	first_type;
			typedef T2	second_type;
			first_type	first;
			second_type	second;

			pair()
			:first(first_type()), second(second_type())
			{}

			pair(const T1 &x, const T2 &y)
			:first(x), second(y)
			{}

			template<class U1, class U2>
			pair(const pair<U1, U2> &p)
			:first(p.first), second(p.second)
			{}

			pair	&operator=(const pair &other)
			{
				if (this != &other)
				{
					this->first = other.first;
					this->second = other.second;
				}
				return (*this);
			}

			operator pair<const T1, const T2>(void) const
			{ return (pair<const T1, const T2>(this->first, this->second)); }
	};

	template<class T1, class T2>
	pair<T1, T2> make_pair(T1 t, T2 u)
	{ return (pair<T1, T2>(t, u)); }

	template<class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		if ((lhs.first == rhs.first) && (lhs.second == rhs.second))
			return (true);
		return (false);
	}

	template<class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return (!(lhs == rhs)); }

	template<class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		if (lhs.first < rhs.first)
			return (true);
		if (lhs.second < rhs.second)
			return (true);
		return (false);
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return (lhs == rhs || lhs < rhs); }

	template<class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return (rhs < lhs); }

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return (lhs == rhs || rhs < lhs); }

	template<class T1, class T2>
	std::ostream	&operator<<(std::ostream &out, const pair<T1, T2> &rhs)
	{
		out << rhs.second;
		return (out);
	}
}