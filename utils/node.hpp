/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:30:47 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/15 02:05:34 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "utils.hpp"
#include "enums.hpp"

namespace ft
{
	template<class T>
	class element
	{
		public :
			typedef T		value_type;
			typedef T*		pointer;

			element()
			: _value(0), _parent(0), _color(E_BLACK)
			{
				_child[E_LEFT] = 0;
				_child[E_RIGHT] = 0;
			}

			element(pointer value)
			: _value(value), _parent(0), _color(E_RED)
			{
				_child[E_LEFT] = new element();
				_child[E_LEFT]->set_parent(this);
				_child[E_RIGHT] = new element();
				_child[E_RIGHT]->set_parent(this);

				// _child[E_LEFT] = std::allocator<T>().allocate(1);
				// std::allocator<T>().construct(_child[E_LEFT], value_type);
				// _child[E_LEFT]->set_parent(this);
				// _child[E_RIGHT] = std::allocator<T>().allocate(1);
				// std::allocator<T>().construct(_child[E_RIGHT], value_type);
				// _child[E_RIGHT]->set_parent(this);
			}

			element(const element &	rhs)
			{ *this = rhs; }

			virtual ~element()
			{
				if (_child[E_LEFT] && !_child[E_LEFT]->get_value())
					delete _child[E_LEFT];
				if (_child[E_RIGHT] && !_child[E_RIGHT]->get_value())
					delete _child[E_RIGHT];
			}

			element &operator=(const element & rhs)
			{
				_value = rhs._value;
				_child[E_LEFT] = rhs._child[E_LEFT];
				_child[E_RIGHT] = rhs._child[E_RIGHT];
				_parent = rhs._parent;
				_color = rhs._color;
				return *this;
			}

			element *get_child(bool dir) const
			{ return _child[dir]; }

			element *get_parent() const
			{ return _parent; }

			element *get_grand_parent() const
			{
				if (_parent)
					return (_parent->get_parent());
				return (0);
			}

			element *get_brother() const
			{
				if (!_parent)
					return (0);
				return (_parent->get_child(!get_side()));
			}

			element *get_uncle() const
			{
				element * tmp = get_parent();
				if (!tmp)
					return (0);
				return (tmp->get_brother());
			}

			pointer get_value() const
			{ return _value; }

			bool get_color() const
			{ return _color; }

			bool get_side() const
			{
				if (!_parent)
					return (0);
				if (_parent->get_child(E_RIGHT) == this)
					return(E_RIGHT);
				return (E_LEFT);
			}

			void set_child(element *rhs, bool dir)
			{ _child[dir] = rhs; }

			void set_brother(element *rhs)
			{ get_brother() = rhs; }

			void set_parent(element *rhs)
			{ _parent = rhs; }

			void set_grand_parent(element *rhs)
			{ get_grand_parent() = rhs; }

			void set_uncle(element *rhs)
			{ get_uncle() = rhs; }

			void set_color(bool rhs)
			{ _color = rhs; }

			void set_value(pointer rhs)
			{ _value = rhs; }

			private:
				pointer		_value;
				element *	_child[2];
				element *	_parent;
				bool		_color;
		};
}