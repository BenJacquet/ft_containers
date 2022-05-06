/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:30:48 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/06 12:36:27 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template<class Iterator>
	class reverse_iterator
	{
		public :
			typename Iterator			iterator_type;
			typename iterator_category	std::iterator_traits<Iterator>::iterator_category;
			typename value_type			std::iterator_traits<Iterator>::value_type;
			typename difference_type	std::iterator_traits<Iterator>::difference_type;
			typename pointer			std::iterator_traits<Iterator>::pointer;
			typename reference			std::iterator_traits<Iterator>::reference;

		
	};
}