/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:30:47 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/15 14:45:54 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "utils.hpp"
#include "enums.hpp"

namespace ft
{
	template<class T>
	class Node
	{
		public:
			typedef T				value_type;
			typedef	Node*			pointer;
			typedef	Node&			reference;

			value_type				data;
			bool					color;
			pointer					left;
			pointer					right;
			pointer					parent;

			Node()
			: data(NULL), color(E_BLACK), left(NULL), right(NULL), parent(NULL)
			{}

			Node(const value_type &x)
			: data(x), color(E_BLACK), left(NULL), right(NULL), parent(NULL)
			{}

			~Node() {}

			reference	operator=(reference rhs)
			{
				if (this != &rhs)
				{
					this->data = rhs.data;
					this->color = rhs.color;
					this->left = rhs.left;
					this->right = rhs.right;
					this->parent = rhs.parent;
				}
				return (*this);
			}
	};
}