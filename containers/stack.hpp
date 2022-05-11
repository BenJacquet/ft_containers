/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:59:59 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/11 13:10:04 by jabenjam         ###   ########.fr       */
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
			typedef Container			container_type;
			typedef T					value_type;
			typedef size_t				size_type;

		protected:
			container_type				c;

		public:
			explicit stack(const container_type& ctnr = container_type())
			: c(ctnr)
			{}

			~stack()
			{}

			stack& operator=(const stack& other)
			{
				this->c = other.c;
				return(*this);
			}

		    value_type& top()
			{ return (this->c.back()); }

			const value_type& top() const
			{ return (this->c.back()); }

			void push (const value_type& val)
			{ this->c.push_back(val); }

			void pop()
			{ this->c.pop_back(); }

			bool empty() const { return(this->c.empty()); }

			size_type size() const { return(this->c.size()); }
	};
}