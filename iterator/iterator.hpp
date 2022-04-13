/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:00:08 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/13 17:49:32 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template <	typename _Category,
				typename _Tp,
				typename _Distance = std::ptrdiff_t,
				typename _Pointer = _Tp *,
				typename _Reference = _Tp &>
	class iterator
	{
		public:
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef ft::random_access_iterator_tag	iterator_category;
			typedef T*								pointer;
			typedef T&								reference;
	};
};