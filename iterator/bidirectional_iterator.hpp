/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:24:14 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/15 02:10:52 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "../iterator/iterator.hpp"
#include "../utils/pair.hpp"
#include "../utils/node.hpp"
#include "../utils/enums.hpp"

namespace ft
{

template < class T >
class bidirectional_iterator : public iterator<bidirectional_iterator_tag, T>
{
	public :
		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef bidirectional_iterator_tag			iterator_category;

		bidirectional_iterator()
		: _node(0)
		{}

		bidirectional_iterator(element<value_type> * elem)
		: _node(elem)
		{}

		bidirectional_iterator(const bidirectional_iterator& rhs)
		: _node(rhs._node)
		{}

		virtual ~bidirectional_iterator()
		{}

		operator bidirectional_iterator<const T>() const
		{ return bidirectional_iterator<const T>(reinterpret_cast<element<const value_type> *>(_node)); }

		bidirectional_iterator& operator=(element<value_type> * rhs)
		{
			_node = rhs;
			return *this;
		}
		bidirectional_iterator& operator=(const bidirectional_iterator& rhs)
		{
			_node = rhs._node;
			return *this;
		}

		bool operator==(const bidirectional_iterator& rhs) const

		{ return (_node == rhs._node); }

		bool operator!=(const bidirectional_iterator& rhs) const

		{ return (_node != rhs._node); }

		reference operator*(void)
		{ return *(_node->get_value()); }

		pointer operator->(void)
		{ return _node->get_value(); }

		bidirectional_iterator& operator++(void)
		{
			_node = _get_nearest(E_RIGHT);
			return *this;
		}

		bidirectional_iterator		operator++(int)
		{
			bidirectional_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		bidirectional_iterator&		operator--(void)
		{
			_node = _get_nearest(E_LEFT);
			return *this;
		}

		bidirectional_iterator		operator--(int)
		{
			bidirectional_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

	private :
		element<value_type> *_node;

		element<value_type> *_get_nearest(bool direction) const
		{
			element<value_type> * tmp = _node;
			if (!tmp)
				return 0;
			if (tmp->get_child(direction) && tmp->get_child(direction)->get_value())
			{
				tmp = tmp->get_child(direction);
				while (tmp->get_child(!direction) && tmp->get_child(!direction)->get_value())
					tmp = tmp->get_child(!direction);
				return tmp;
			}
			else if (tmp->get_parent())
			{
				if (tmp->get_side() != direction)
					return (tmp->get_parent());
				else
				{
					while (tmp->get_parent() && tmp->get_side() == direction)
						tmp = tmp->get_parent();
					if (!tmp->get_parent())
						return(_node->get_child(direction));
					return(tmp->get_parent());
				}
			}
			else
				return _node->get_child(direction);
		}
};
}