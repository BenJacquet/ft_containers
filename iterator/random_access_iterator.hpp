/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:24:35 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/22 11:36:24 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

/*
** RANDOM ACCESS ITERATOR (FOR VECTOR)
*/

namespace ft
{
	template<class T>
	class random_access_iterator : public ft::iterator<random_access_iterator_tag, T>
	{
		public:
			typedef T										value_type;
			typedef std::ptrdiff_t							difference_type;
			typedef typename ft::random_access_iterator_tag	iterator_category;
			typedef T*										pointer;
			typedef T&										reference;

			/*
			** All iterator Categories Requirements
			*/

			random_access_iterator(const random_access_iterator &rhs)
			:_current(rhs._current) {}

			random_access_iterator(reference rhs)
			: _current(&rhs) {}

			random_access_iterator(pointer rhs)
			:_current(rhs) {}

			operator random_access_iterator<const T>()
			{ return (random_access_iterator<const T>(*(_current))); }

			random_access_iterator& operator=(pointer rhs)
			{
				_current = rhs;
				return (*this);
			}

			random_access_iterator& operator=(random_access_iterator &rhs)
			{
				_current = rhs._current;
				return (*this);
			}

			random_access_iterator&	operator=(const random_access_iterator &rhs)
			{
				_current = rhs._current;
				return (*this);
			}

			~random_access_iterator() {}

			pointer base() const
			{ return (_current); }

			random_access_iterator& operator++()
			{
				_current++;
				return (*this);
			}

			random_access_iterator operator++(int)
			{ return (random_access_iterator(_current++)); }

			/*
			** Forward iterator Requirements
			*/

			reference operator*() const
			{ return (*(_current)); }

			pointer operator->() const
			{ return (_current); }

			random_access_iterator()
			: _current(0) {};

			/*
			** Bidirectional iterator Requirements
			*/

			random_access_iterator& operator--()
			{
				_current--;
				return (*this);
			}

			random_access_iterator operator--(int)
			{ return (random_access_iterator(_current--)); }

			/*
			** Random Access iterator Requirements
			*/

			random_access_iterator operator+(difference_type n)
			{ return (random_access_iterator(_current + n)); }

			random_access_iterator operator-(difference_type n) const
			{ return (random_access_iterator(_current - n)); }

			random_access_iterator& operator+=(difference_type n)
			{
				_current += n;
				return (*this);
			}

			random_access_iterator& operator-=(difference_type n)
			{
				_current -= n;
				return (*this);
			}

			reference operator[](difference_type n) const
			{ return (_current[n]); }

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

	template<class iterator>
	random_access_iterator<iterator> operator+(typename random_access_iterator<iterator>::difference_type n, const random_access_iterator<iterator>& it)
	{ return (random_access_iterator<iterator>(it.base() + n)); }

	template<class iterator>
	random_access_iterator<iterator> operator-(typename random_access_iterator<iterator>::difference_type n, const random_access_iterator<iterator>& it)
	{ return (random_access_iterator<iterator>(it.base() - n)); }

	template <typename IteratorL, typename IteratorR>
	typename ft::random_access_iterator<IteratorL>::difference_type
	operator-(const ft::random_access_iterator<IteratorL> lhs,
			const ft::random_access_iterator<IteratorR> rhs)
	{ return (lhs.base() - rhs.base()); }

		template <typename IteratorL, typename IteratorR>
	typename ft::random_access_iterator<IteratorL>::difference_type
	operator+(const ft::random_access_iterator<IteratorL> lhs,
			const ft::random_access_iterator<IteratorR> rhs)
	{ return (lhs.base() + rhs.base()); }

}