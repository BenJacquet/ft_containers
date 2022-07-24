/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:59:14 by jabenjam          #+#    #+#             */
/*   Updated: 2022/07/24 19:43:46 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	// template <class InputIterator1, class InputIterator2>
	// bool equal(InputIterator1 first1, InputIterator1 last1,
	// 			InputIterator2 first2)
	// {
	// 	for (;first1 != last1; first1++, first2++)
	// 	{
	// 		if (!(*first1 == *first2))
	// 			return (false);
	// 	}
	// 	return (true);
	// };

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2)
	{
		for (; first1 != last1; first1++)
		{
			if (*first1 != *first2)
				return false;
			first2++;
		}
		return true;
	};

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		for ( ; first1 != last1; first1++)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			if (*first1 < *first2)
				return true;
			first2++;
		}
		return (first2 != last2);
	};
}
