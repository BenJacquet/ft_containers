/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:00:08 by jabenjam          #+#    #+#             */
/*   Updated: 2022/07/25 00:31:26 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

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

	template <	class Category,
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

	/*
	** RANDOM ACCESS ITERATOR (FOR VECTOR)
	*/

	template<class iterator>
	class random_access_iterator
	{
		public:
			typedef iterator								value_type;
			typedef std::ptrdiff_t							difference_type;
			typedef typename ft::random_access_iterator_tag	iterator_category;
			typedef iterator*								pointer;
			typedef iterator&								reference;

			/*
			** All iterator Categories Requirements
			*/

			random_access_iterator(const random_access_iterator &rhs)
			:_current(rhs._current) {}

			random_access_iterator(reference rhs)
			: _current(&rhs) {}

			random_access_iterator(pointer rhs)
			:_current(rhs) {}

			operator random_access_iterator<const iterator>()
			{ return random_access_iterator<const iterator>(*(this->_current)); }

			random_access_iterator&
			operator=(random_access_iterator &rhs)
			{
				this->_current = rhs._current;
				return (*this);
			}

			random_access_iterator&
			operator=(const random_access_iterator &rhs)
			{
				this->_current = rhs._current;
				return (*this);
			}

			~random_access_iterator() {}

			pointer base() const
			{ return (this->_current); }

			random_access_iterator& operator++()
			{
				this->_current++;
				return (*this);
			}

			random_access_iterator operator++(int)
			{ return (random_access_iterator(this->_current++)); }

			/*
			** Forward iterator Requirements
			*/

			reference operator*() const
			{ return (*(this->_current)); }

			pointer operator->() const
			{ return (this->_current); }

			random_access_iterator()
			: _current(0) {};

			/*
			** Bidirectional iterator Requirements
			*/

			random_access_iterator& operator--()
			{
				this->_current--;
				return (*this);
			}

			random_access_iterator operator--(int)
			{ return (random_access_iterator(this->_current--)); }

			/*
			** Random Access iterator Requirements
			*/

			random_access_iterator operator+(difference_type n) const
			{ return (random_access_iterator(this->_current + n)); }

			difference_type operator-(const random_access_iterator& rhs) const
			{ return (this->_current - rhs._current); }

			random_access_iterator operator-(difference_type n) const
			{ return (random_access_iterator(this->_current - n)); }

			random_access_iterator& operator+=(difference_type n)
			{
				this->_current += n;
				return (*this);
			}

			random_access_iterator& operator-=(difference_type n)
			{
				this->_current -= n;
				return (*this);
			}

			reference operator[](difference_type n)
			{ return (this->_current[n]); }

		private:
			pointer _current;
	};

	/*
	** NON MEMBER FUNCTIONS OF RANDOM ACCESS ITERATOR (FOR VECTOR)
	*/

	template <typename iteratorL, typename iteratorR>
	bool operator==(const random_access_iterator<iteratorL> &lhs,
				const random_access_iterator<iteratorR> &rhs)
	{ return (lhs.base() == rhs.base()); };

	template <typename iteratorL, typename iteratorR>
	bool operator!=(const random_access_iterator<iteratorL> &lhs,
				const random_access_iterator<iteratorR> &rhs)
	{ return (lhs.base() != rhs.base()); };

	template <typename iteratorL, typename iteratorR>
	bool operator<(const random_access_iterator<iteratorL> &lhs,
				const random_access_iterator<iteratorR> &rhs)
	{ return (lhs.base() < rhs.base()); };

	template <typename iteratorL, typename iteratorR>
	bool operator>(const random_access_iterator<iteratorL> &lhs,
				const random_access_iterator<iteratorR> &rhs)
	{ return (lhs.base() > rhs.base()); };

	template <typename iteratorL, typename iteratorR>
	bool operator<=(const random_access_iterator<iteratorL> &lhs,
				const random_access_iterator<iteratorR> &rhs)
	{ return (lhs.base() <= rhs.base()); };

	template <typename iteratorL, typename iteratorR>
	bool operator>=(const random_access_iterator<iteratorL> &lhs,
				const random_access_iterator<iteratorR> &rhs)
	{ return (lhs.base() >= rhs.base()); };

	/*
	** REVERSE ITERATOR (SUPPORTS UP TO RANDOM ACCESS ITERATOR)
	*/

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

			reverse_iterator(const reverse_iterator &rhs)
			:_current(rhs._current) {}

			reverse_iterator(pointer rhs)
			:_current(rhs) {}

			explicit reverse_iterator(iterator_type t)
			:_current(t) {}

			reverse_iterator()
			: _current() {};

			~reverse_iterator() {}

			reverse_iterator&
			operator=(reverse_iterator &rhs)
			{
				this->_current = rhs._current;
				return (*this);
			}

			reverse_iterator&
			operator=(const reverse_iterator &rhs)
			{
				this->_current = rhs._current;
				return (*this);
			}

			iterator_type base() const
			{ return (this->_current); }

			reference operator*() const
			{
				iterator_type tmp = this->_current;
				return(*(--tmp));
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
			{ return (this->_current[n]); }

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
	{ return (lhs.base() < rhs.base()); };

	template <class iteratorL, class iteratorR>
	bool operator>(const reverse_iterator<iteratorL> &lhs,
				const reverse_iterator<iteratorR> &rhs)
	{ return (lhs.base() > rhs.base()); };

	template <class iteratorL, class iteratorR>
	bool operator<=(const reverse_iterator<iteratorL> &lhs,
				const reverse_iterator<iteratorR> &rhs)
	{ return (lhs.base() <= rhs.base()); };

	template <class iteratorL, class iteratorR>
	bool operator>=(const reverse_iterator<iteratorL> &lhs,
				const reverse_iterator<iteratorR> &rhs)
	{ return (lhs.base() >= rhs.base()); };

	template< class iterator >
	reverse_iterator<iterator> operator+( typename reverse_iterator<iterator>::difference_type n, const reverse_iterator<iterator>& it )
	{ return(reverse_iterator<iterator>(it.base() - n)); }

	template< class iterator >
	typename reverse_iterator<iterator>::difference_type operator-( const reverse_iterator<iterator>& lhs, const reverse_iterator<iterator>& rhs )
	{ return (rhs.base() - lhs.base()); }
};