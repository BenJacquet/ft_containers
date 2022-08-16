/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:24:14 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/16 20:11:25 by jabenjam         ###   ########.fr       */
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
	template<class Node_type, class Value_type>
	class bidirectional_iterator
	{
	public:
		typedef Node_type						node_type;
		typedef Value_type						value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef value_type*						pointer;
		typedef value_type&						reference;
		typedef std::bidirectional_iterator_tag	iterator_category;

		node_type		*current;

		bidirectional_iterator()
		:current(NULL), _end(NULL)
		{}

		bidirectional_iterator(node_type *ptr)
		:current(ptr), _end(NULL)
		{}

		bidirectional_iterator(node_type *ptr, node_type *end)
		:current(ptr), _end(end)
		{}

		bidirectional_iterator(const bidirectional_iterator &copy)
		{ *this = copy; }

		~bidirectional_iterator() {}

		bidirectional_iterator	&operator=(const bidirectional_iterator &other)
		{
			if (this != &other)
			{
				this->current = other.current;
				this->_end = other._end;
			}
			return (*this);
		}

		reference	operator*(void)
		{ return (this->current->data); }

		const value_type	&operator*(void) const
		{ return (this->current->data); }

		value_type	*operator->(void)
		{ return (&this->operator*()); }

		const value_type	*operator->(void) const
		{ return (&this->operator*()); }

		bidirectional_iterator	operator++(int)
		{
			bidirectional_iterator	it(*this);

			this->current = this->_increase();
			return (it);
		}

		bidirectional_iterator	&operator++(void)
		{
			this->current = this->_increase();
			return (*this);
		}

		bidirectional_iterator	operator--(int)
		{
			bidirectional_iterator	it(*this);

			this->current = this->_decrease();
			return (it);
		}

		bidirectional_iterator	&operator--(void)
		{
			this->current = this->_decrease();
			return (*this);
		}

		operator bidirectional_iterator<const Node_type, const Value_type>(void) const
		{ return (bidirectional_iterator<const Node_type, const Value_type>(this->current, this->_end)); }

	private:
		node_type			*_end;

		node_type	*_minimum(node_type *node)
		{
			node_type	*current = node;

			while (current->left != this->_end)
				current = current->left;
			return (current);
		}

		node_type	*_maximum(node_type *node)
		{
			node_type	*current = node;

			while (current->right != this->_end)
				current = current->right;
			return (current);
		}

		node_type	*_topIncrease(node_type *node)
		{
			node_type	*current = node;
			node_type	*parent = current->parent;

			while (parent != NULL && current == parent->right)
			{
				current = parent;
				parent = parent->parent;
			}
			if (parent == NULL)
				current = this->_end;
			else
				current = parent;
			return (current);
		}

		node_type	*_topDecrease(node_type *node)
		{
			node_type	*current = node;
			node_type	*parent = current->parent;

			while (parent != NULL && current == parent->left)
			{
				current = parent;
				parent = parent->parent;
			}
			if (parent == NULL)
				current = this->_end;
			else
				current = parent;
			return (current);
		}

		node_type	*_increase(void)
		{
			if (this->current == this->_end && this->_end->parent != NULL)
				return (this->_minimum(this->current->parent));
			if (this->current->right == this->_end)
				return (this->_topIncrease(this->current));
			return (this->_minimum(this->current->right));
		}

		node_type	*_decrease(void)
		{
			if (this->current == this->_end && this->_end->parent != NULL)
				return (this->_maximum(this->current->parent));
			if (this->current->left == this->_end)
				return (this->_topDecrease(this->current));
			return (this->_maximum(this->current->left));
		}
	};

	template<class Tx, class Ux, class Ty, class Uy>
	bool	operator==(const bidirectional_iterator<Tx, Ux> &x, const bidirectional_iterator<Ty, Uy> &y)
	{
		if (x.current == y.current)
			return (true);
		return (false);
	}

	template<class Tx, class Ux, class Ty, class Uy>
	bool	operator!=(const bidirectional_iterator<Tx, Ux> &x, const bidirectional_iterator<Ty, Uy> &y)
	{
		if (x.current != y.current)
			return (true);
		return (false);
	}
}