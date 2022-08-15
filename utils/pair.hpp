/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:30:25 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/15 02:11:21 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace ft
{
	template< class T1, class T2>
	struct pair
	{
		public :
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;

			pair()
			:first(first_type()), second(second_type())
			{}

			pair(const T1& x, const T2& y)
			:first(x), second(y)
			{}

			template<class U1, class U2>
			pair(const pair<U1, U2>& p)
			:first(p.first), second(p.second)
			{}

			pair(const pair& p)
			:first(p.first), second(p.second)
			{}

			pair& operator=(const pair& rhs)
			{
				first = rhs.first;
				second = rhs.second;
				return *this;
			}
	};
	template< class T1, class T2 >
	pair<T1,T2> make_pair(T1 t, T2 u)
	{ return(pair<T1, T2>(t, u)); }

	template< class T1, class T2 >
	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template< class T1, class T2 >
	bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (!(lhs == rhs)); }

	template< class T1, class T2 >
	bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

	template< class T1, class T2 >
	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (!(lhs > rhs)); }

	template< class T1, class T2 >
	bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (!(lhs == rhs || lhs < rhs)); }

	template< class T1, class T2 >
	bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (!(lhs < rhs)); }
}