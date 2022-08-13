/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:00:08 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/13 17:39:15 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "../utils/utils.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

	/*
	** ITERATOR TAGS
	** Empty types used to differenciate the iterators
	*/

	struct input_iterator_tag {};

	struct output_iterator_tag {};

	struct forward_iterator_tag : public input_iterator_tag {};

	struct bidirectional_iterator_tag : public forward_iterator_tag {};

	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/*
	** ITERATOR TRAITS
	*/

	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
	};

	/*
	** ITERATOR TRAITS POINTER
	*/

	template <class Iterator>
	class iterator_traits<Iterator*>
	{
		typedef Iterator								value_type;
		typedef std::ptrdiff_t							difference_type;
		typedef random_access_iterator_tag				iterator_category;
		typedef Iterator*								pointer;
		typedef Iterator&								reference;
	};

	/*
	** ITERATOR TRAITS CONST
	*/

	template <class Iterator>
	class iterator_traits<const Iterator*>
	{
		typedef Iterator								value_type;
		typedef std::ptrdiff_t							difference_type;
		typedef random_access_iterator_tag				iterator_category;
		typedef const Iterator*							pointer;
		typedef const Iterator&							reference;
	};

	/*
	** ITERATOR
	*/

	template <class Category,
				class T,
				class Distance = std::ptrdiff_t,
				class Pointer = T*,
				class Reference = T&>
	class iterator
	{
		public:
			typedef Category						iterator_category;
			typedef T								value_type;
			typedef Distance						difference_type;
			typedef Pointer							pointer;
			typedef Reference						reference;
	};
};