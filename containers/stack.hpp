/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:59:59 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/04 14:53:01 by jabenjam         ###   ########.fr       */
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
			container_type				sub_container;

		public:
			explicit stack (const container_type& ctnr = container_type());

		    value_type& top()
			{ return (this->sub_container.back()); }

			const value_type& top() const
			{ return (this->sub_container.back()); }

			void push (const value_type& val)
			{ this->sub_container.push_back(val); }

			void pop()
			{ this->sub_container.pop_back(); }
	};
}