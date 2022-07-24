/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:59:14 by jabenjam          #+#    #+#             */
/*   Updated: 2022/07/25 00:37:49 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2)
	{
		for (; first1 != last1; first1++, first2++)
		{
			if (*first1 != *first2)
				return false;
		}
		return true;
	};

	template< class InputIterator1, class InputIterator2, class BinaryPredicate >
	bool equal(InputIterator1 first1, InputIterator2 last1, InputIterator2 first2, BinaryPredicate p)
	{
		for ( ; first1 != last1; first1++, first2++)
		{
			if (!p(*first1, *first2))
				return false;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		for ( ; first1 != last1; first1++, first2++)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			if (*first1 < *first2)
				return true;
		}
		return (first2 != last2);
	};

	template< class InputIterator1, class InputIterator2, class Compare >
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		for ( ; first1 != last1; first1++, first2++)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			if (comp(*first1, *first2))
				return true;
		}
		return true;
	}
}
