/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:24:50 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/22 14:38:39 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../iterator/random_access_iterator.hpp"

namespace ft
{
	template<typename T, typename Alloc>
	class vector
	{
		private:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef T&											reference;
			typedef const T&									const_reference;
			typedef T*											pointer;
			typedef const T*									const_pointer;
			typedef random_access_iterator<T>					iterator;
			typedef	random_access_iterator<const T>				const_iterator;
			typedef	reverse_iterator<iterator>					reverse_iterator;
			typedef	reverse_iterator<const iterator>			const_reverse_iterator;
			typedef	iterator_traits<iterator>::difference_type	difference_type;
			typedef	size_t										size_type;
		public:
			vector (const allocator_type& alloc = allocator_type());//default
			vector (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type());//fill
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type());//range
			vector (const vector& x);//copy

			~vector ();
	};
};