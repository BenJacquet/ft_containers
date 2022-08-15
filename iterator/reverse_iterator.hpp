/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:28:49 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/15 02:10:39 by jabenjam         ###   ########.fr       */
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

			reverse_iterator operator+(difference_type n) const
			{ return reverse_iterator(_current - n); }

			reverse_iterator operator-(difference_type n) const
			{ return reverse_iterator(_current + n); }

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

template< class Iter >
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
{ return(reverse_iterator<Iter>(it.base() - n)); }

template< class Iter >
reverse_iterator<Iter> operator-(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
{ return(reverse_iterator<Iter>(it.base() + n)); }

};