/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:28:49 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/17 13:01:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

namespace ft
{
	template < class Iterator>
	class reverse_iterator
	{
		public :
			typedef Iterator								iterator_type;
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;

			reverse_iterator(void)
			: _current(iterator_type()) {};

			explicit reverse_iterator(iterator_type t)//
			:_current(t) {}

			template< class U >
			reverse_iterator(const reverse_iterator<U> & rhs)
			{ *this = rhs; }

			virtual ~reverse_iterator(void) 
			{}

			template< class U >
			reverse_iterator& operator=(const reverse_iterator<U>& rhs)
			{
				_current = rhs.base();
				return *this;
			}

			iterator_type base() const
			{ return _current; }

			reference operator*() const
			{
				iterator_type tmp = _current;
				return(*(--tmp));
			}

			pointer operator->() const
			{
				iterator_type tmp = _current;
				return (&(*(--tmp)));
			}

			reference operator[](difference_type n) const
			{ return (_current[-n - 1]); }

			reverse_iterator& operator++()
			{
				_current--;
				return *this;
			}

			reverse_iterator& operator--()
			{
				_current++;
				return *this;
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}


			reverse_iterator operator+(difference_type n) {
				return reverse_iterator(this->_current - n);
			}

			reverse_iterator operator-(difference_type n) {
				return reverse_iterator(this->_current + n);
			}

			reverse_iterator& operator+=(difference_type n)
			{
				_current -= n;
				return *this;
			}

			reverse_iterator& operator-=(difference_type n)
			{
				_current += n;
				return *this;
			}

		protected :
			iterator_type	_current;
	};

	template< class Iterator1, class Iterator2 >
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{ return lhs.base() == rhs.base(); }

	template< class Iterator1, class Iterator2 >
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{ return lhs.base() != rhs.base(); }

	template< class Iterator1, class Iterator2 >
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{ return lhs.base() < rhs.base(); }

	template< class Iterator1, class Iterator2 >
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template< class Iterator1, class Iterator2 >
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{ return lhs.base() > rhs.base(); }

	template< class Iterator1, class Iterator2 >
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{ return lhs.base() >= rhs.base(); }

	template <class Iter>
	ft::reverse_iterator<Iter> operator+(typename ft::reverse_iterator<Iter>::difference_type n, const ft::reverse_iterator<Iter>& it)
	{
		return it + n;
	};
	template <class Iter>
	typename ft::reverse_iterator<Iter>::difference_type operator-(const ft::reverse_iterator<Iter>& lhs, const ft::reverse_iterator<Iter>& rhs)
	{
		return rhs.base() - lhs.base();
	};
	template <class Iter1, class Iter2>
	typename ft::reverse_iterator<Iter1>::difference_type operator-(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)
	{
		return rhs.base() - lhs.base();
	};
};