/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:28:49 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/13 17:43:19 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

	/*
	** REVERSE ITERATOR (SUPPORTS UP TO RANDOM ACCESS ITERATOR)
	*/
namespace ft
{
	template<class iterator>
	class reverse_iterator
	{
		public:
			typedef iterator								iterator_type;
			typedef typename iterator::iterator_category	iterator_category;
			typedef typename iterator::value_type			value_type;
			typedef typename iterator::difference_type		difference_type;
			typedef typename iterator::pointer				pointer;
			typedef typename iterator::reference			reference;

			template<class T>
			reverse_iterator(const reverse_iterator<T>& rhs)
			{ *this = rhs; }

			reverse_iterator(pointer rhs)
			:_current(rhs) {}

			explicit reverse_iterator(iterator_type t)
			:_current(t) {}

			reverse_iterator()
			: _current(iterator_type()) {};

			virtual ~reverse_iterator() {}

			template<class T>
			reverse_iterator& operator=(const reverse_iterator<T>& rhs)
			{
				this->_current = rhs.base();
				return (*this);
			}

			iterator_type base() const
			{ return (this->_current); }

			reference operator*() const
			{
				iterator_type tmp = this->_current;
				return (*(--tmp));
			}

			pointer operator->() const
			{
				iterator_type tmp = this->_current;
				return (&(*(--tmp)));
			}

			reverse_iterator& operator++()
			{
				this->_current--;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = (*this);
				++(*this);
				return (tmp);
			}

			reverse_iterator& operator--()
			{
				this->_current++;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = (*this);
				--(*this);
				return (tmp);
			}

			reverse_iterator operator+(difference_type n) const
			{ return (reverse_iterator(this->_current - n)); }

			reverse_iterator operator-(difference_type n) const
			{ return (reverse_iterator(this->_current + n)); }

			reverse_iterator& operator+=(difference_type n)
			{
				this->_current -= n;
				return (*this);
			}

			reverse_iterator& operator-=(difference_type n)
			{
				this->_current += n;
				return (*this);
			}

			reference operator[](difference_type n)
			{ return (this->_current[(-n) - 1]); }

		private:
			iterator_type _current;
	};

	/*
	** NON MEMBER FUNCTIONS OF REVERSE ITERATOR
	*/

	template <class iteratorL, class iteratorR>
	bool operator==(const reverse_iterator<iteratorL> &lhs,
				const reverse_iterator<iteratorR> &rhs)
	{ return (lhs.base() == rhs.base()); };

	template <class iteratorL, class iteratorR>
	bool operator!=(const reverse_iterator<iteratorL> &lhs,
				const reverse_iterator<iteratorR> &rhs)
	{ return (lhs.base() != rhs.base()); };

	template <class iteratorL, class iteratorR>
	bool operator<(const reverse_iterator<iteratorL> &lhs,
				const reverse_iterator<iteratorR> &rhs)
	{ return (lhs.base() > rhs.base()); };

	template <class iteratorL, class iteratorR>
	bool operator>(const reverse_iterator<iteratorL> &lhs,
				const reverse_iterator<iteratorR> &rhs)
	{ return (lhs.base() < rhs.base()); };

	template <class iteratorL, class iteratorR>
	bool operator<=(const reverse_iterator<iteratorL> &lhs,
				const reverse_iterator<iteratorR> &rhs)
	{ return (lhs.base() >= rhs.base()); };

	template <class iteratorL, class iteratorR>
	bool operator>=(const reverse_iterator<iteratorL> &lhs,
				const reverse_iterator<iteratorR> &rhs)
	{ return (lhs.base() <= rhs.base()); };

	template<class iterator>
	reverse_iterator<iterator> operator+(typename reverse_iterator<iterator>::difference_type n, const reverse_iterator<iterator>& it)
	{ return (reverse_iterator<iterator>(it.base() - n)); }

	template<class iterator>
	typename reverse_iterator<iterator>::difference_type operator-(const reverse_iterator<iterator>& lhs, const reverse_iterator<iterator>& rhs)
	{ return (rhs.base() - lhs.base()); }
}