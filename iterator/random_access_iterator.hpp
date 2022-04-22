/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_accessiterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:01:18 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/13 17:43:29 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"
#include "iterator.hpp"

namespace ft
{
	using ft::iterator_traits;
	using ft::iterator;
	template<typename Iterator>
	class random_access_iterator
	{
		protected:
			Iterator _current;
			typedef iterator_traits<Iterator>				_traits_type;

		public:
			typedef Iterator								value_type;
			typedef std::ptrdiff_t							difference_type;
			typedef ft::random_access_iterator_tag			iterator_category;
			typedef Iterator*								pointer;
			typedef Iterator&								reference;

			/*
			** All Iterator Categories Requirements
			*/

			random_access_iterator(const Iterator &rhs)
			:current(rhs) {};

			operator=(const Iterator &rhs)
			{*this = rhs};

			~random_access_iterator() {};

			const Iterator&
			base() const
			{ return (this->_current); };

			Iterator&
			operator++()
			{
				++this->_current;
				return (*this);
			};

			Iterator
			operator++(int)
			{ return (Iterator(this->_current++)); };

			/*
			** Forward Iterator Requirements
			*/

			template<typename IteratorL, typename IteratorR>
			bool
			operator==(const Iterator<IteratorL> &lhs,
					const Iterator<IteratorR> &rhs)
			{ return (lhs.base() == rhs.base()); };

			template<typename IteratorL, typename IteratorR>
			bool
			operator!=(const Iterator<IteratorL> &lhs,
					const Iterator<IteratorR> &rhs)
			{ return (lhs.base() != rhs.base()); };

			reference
			operator*() const
			{ return (*(this->_current)); };

			pointer
			operator->() const
			{ return (this->_current); };

			random_access_iterator()
			: _current() {};

			/*
			** Bidirectional Iterator Requirements
			*/

			Iterator&
			operator--()
			{
				--this->_current;
				return (*this);
			};

			Iterator
			operator--(int)
			{ return (Iterator(this->_current--)); };

			/*
			** Random Access Iterator Requirements
			*/

			// AJOUTER SUPPORT NON CONST ?

			Iterator
			operator+(difference_type n) const
			{ return (this->_current + n); };

			Iterator
			operator-(difference_type n) const
			{ return (this->_current - n); };

			template<typename IteratorL, typename IteratorR>
			bool
			operator<(const Iterator<IteratorL> &lhs,
					const Iterator<IteratorR> &rhs)
			{ return (lhs.base() < rhs.base()); };

			template<typename IteratorL, typename IteratorR>
			bool
			operator>(const Iterator<IteratorL> &lhs,
					const Iterator<IteratorR> &rhs)
			{ return (lhs.base() > rhs.base()); };

			template<typename IteratorL, typename IteratorR>
			bool
			operator<=(const Iterator<IteratorL> &lhs,
					const Iterator<IteratorR> &rhs)
			{ return (lhs.base() <= rhs.base()); };

			template<typename IteratorL, typename IteratorR>
			bool
			operator>=(const Iterator<IteratorL> &lhs,
					const Iterator<IteratorR> &rhs)
			{ return (lhs.base() >= rhs.base()); };

			Iterator&
			operator+=(difference_type n)
			{
				this->_current += n);
				return (*this);
			};

			Iterator&
			operator-=(difference_type n)
			{
				this->_current -= n);
				return (*this);
			};

			reference
			operator[](difference_type n) const
			{ return (this->_current[n]); };
	};
};