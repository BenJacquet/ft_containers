/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:59:59 by jabenjam          #+#    #+#             */
/*   Updated: 2022/07/28 22:43:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		public:
			typedef Container								container_type;
			typedef typename Container::value_type			value_type;
			typedef typename Container::size_type			size_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;

		protected:
			Container				c;

		public:
			explicit stack(const Container& ctnr = Container())
			: c(ctnr)
			{}

			stack(const stack& other)
			: c(other.c)
			{}

			virtual ~stack()
			{}

			stack& operator=(const stack& rhs)
			{
				this->c = rhs.c;
				return (*this);
			}

			/*
			** ELEMENT ACCESS
			*/

			reference top()
			{ return (this->c.back()); }

			const_reference top() const
			{ return (this->c.back()); }

			/*
			** MODIFIERS
			*/

			void push (const value_type& val)
			{ this->c.push_back(val); }

			void pop()
			{ this->c.pop_back(); }

			/*
			** CAPACITY
			*/

			bool empty() const
			{ return (this->c.empty()); }

			size_type size() const
			{ return (this->c.size()); }
	};

	/*
	** Non Member Functions
	*/

	template <class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.c == rhs.c); }

	template <class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (!(lhs == rhs)); }

	template <class T, class Container>
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.c < rhs.c); }

	template <class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (!(rhs < lhs)); }

	template <class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (rhs < lhs); }

	template <class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (!(lhs < rhs)); }
}