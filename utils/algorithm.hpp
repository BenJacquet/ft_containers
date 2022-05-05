/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:59:14 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/05 13:33:50 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2)
	{
		for (;first1 != last1; first1++, first2++)
		{
			if (!(*first1 == *first2))
				return (false);
		}
		return (true);
	};

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		for (;first1 != last1; first1++, first2++)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
		}
		return (first2 != last2);
	};
}
