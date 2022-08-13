/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:30:47 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/01 16:36:29 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "utils.hpp"

namespace ft
{
	template<class T>
	class node
	{
		public:
			typedef T	value_type;
			typedef T*	pointer;

		private:
			pointer _value;
			bool	_color;
			node	*_parent;
			node	*_child[2];

		public:
			node()
			: _value(NULL), _color(E_BLACK), _parent(NULL)
			{
				this->_child[E_LEFT] = NULL;
				this->_child[E_RIGHT] = NULL;
			}

			node(pointer value)
			: _value(value), _color(E_RED), _parent(NULL)
			{
				this->_child[E_LEFT](create_new_node(this));
				this->_child[E_RIGHT](create_new_node(this));
			}

			node(const node& rhs)
			{ *this = rhs; }

			virtual ~node()
			{
				if (this->_child[E_LEFT] && this->_child[E_LEFT]->empty())
					delete this->_child[E_LEFT];
				if (this->_child[E_RIGHT] && this->_child[E_RIGHT]->empty())
					delete this->_child[E_RIGHT];
			}

			node& operator=(const node& rhs)
			{
				this->_value = rhs._value;
				this->_color = rhs._color;
				this->_parent = rhs._parent;
				this->_child[E_LEFT] = rhs._child[E_LEFT];
				this->_child[E_RIGHT] = rhs._child[E_RIGHT];
				return (*this);
			}

			bool empty()
			{ return (!this->get_value()); }

			node *create_new_node(const node* parent)
			{
				node *new_node = new node();
				new_node->_parent = parent;
				return (new_node);
			}

			/*
			** GETTERS
			*/

			pointer get_value() const
			{ return (this->_value); }

			bool get_color() const
			{ return (this->_color); }

			node *get_grandparent() const
			{ return (this->_parent ? this->_parent->get_parent() : NULL); }

			node *get_uncle() const
			{ return (this->_parent ? this->_parent->get_twin() : NULL); }

			node *get_parent() const
			{ return (this->_parent); }

			node *get_twin() const
			{ return (this->_parent ? this->_parent->get_child(!get_direction()) : NULL); }

			node *get_child(bool direction) const
			{ return (this->_child[direction]); }

			node *get_left() const
			{ return (this->_child[E_LEFT]); }

			node *get_right() const
			{ return (this->_child[E_RIGHT]); }

			bool get_direction() const
			{
				if (!this->_parent || this->_parent->get_child(E_LEFT) == this)
					return (E_LEFT);
				return (E_RIGHT);
			}

			/*
			** SETTERS
			*/

			void set_value(pointer value)
			{ this->_value = value; }

			void set_color(bool color)
			{ this->_color = color; }

			void set_parent(node *parent)
			{ this->_parent = parent; }

			void set_child(node *child, bool direction)
			{ this->_child[direction] = child; }

			void set_left(node *left)
			{ this->_child[E_LEFT] = left; }

			void set_right(node *right)
			{ this->_child[E_RIGHT] = right; }
	};
}