/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:24:14 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/22 09:53:11 by jabenjam         ###   ########.fr       */
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
	template<typename Node_type, typename Value_type>
	class bidirectional_iterator
	{
		public :
			typedef	std::ptrdiff_t							difference_type;
			typedef Node_type								node_type;
			typedef	Value_type								value_type;
			typedef	value_type*								pointer;
			typedef	value_type&								reference;
			typedef	ft::bidirectional_iterator_tag			iterator_category;

			bidirectional_iterator() : _elem(), _root(), _sentinel()
			{}

			bidirectional_iterator(bidirectional_iterator const & src) : _elem(src._elem),
				_root(src._root), _sentinel(src._sentinel)
			{ }

			bidirectional_iterator(node_type * elem, node_type * root) : _elem(elem)
			{
				this->_root = root;
				this->_sentinel = root->parent;
			}

			virtual ~bidirectional_iterator() {}

			bidirectional_iterator&	operator=(const bidirectional_iterator &to_copy)
			{
				if (this != &to_copy)
				{
					this->_elem = to_copy._elem;
					this->_root = to_copy._root;
					this->_sentinel = to_copy._sentinel;
				}
				return *this;
			}

			operator bidirectional_iterator<const Node_type, const Value_type>() const
			{ return bidirectional_iterator<const Node_type, const Value_type>(this->_elem, this->_root); }

			reference operator*()
			{ return (this->_elem->key_val); }

			reference operator*() const
			{ return (this->_elem->key_val); }

			pointer operator->()
			{ return (&this->operator*()); }

			pointer operator->() const
			{ return (&this->operator*()); }

			bidirectional_iterator& operator++()
			{
				this->_elem = _found_next_one(_elem);
				return *this;
			}

			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator rtn(*this);
				operator++();
				return (rtn);
			}

			bidirectional_iterator& operator--()
			{
				this->_elem = _found_prec(_elem);
				return *this;
			}

			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator rtn(*this);
				operator--();
				return (rtn);
			}

			node_type	* base() const { return this->_elem; }

		private :
			node_type	*_elem;
			node_type	*_root;
			node_type	*_sentinel;

			node_type	* _found_next_one(node_type	* node)
			{
				if (node == _maximum(this->_root) || node == this->_sentinel)
					return this->_sentinel;
				if (node->right != this->_sentinel)
					return (_minimum(node->right));
				if (node != node->parent->left)
				{
					while (node != node->parent->left)
						node = node->parent;
				}
				node = node->parent;
				return node;
			}

			node_type	* _found_prec(node_type	* node)
			{
				if (node == this->_sentinel)
					return (_maximum(this->_root));
				if (node == _minimum(this->_root))
					return this->_sentinel;
				if (node->left != this->_sentinel)
					return (_maximum(node->left));
				if (node != node->parent->right)
				{
					while (node != node->parent->right)
						node = node->parent;
				}
				node = node->parent;
				return node;
			}

			node_type	* _minimum(node_type	* node)
			{
				while (node->left != this->_sentinel)
					node = node->left;
				return node;
			}

			node_type	* _maximum(node_type	* node)
			{
				while (node->right != this->_sentinel)
				{
					node = node->right;
				}
				return node;
			}
	};

	template<typename Tx, typename Xx, typename Ty, typename Xy>
	bool operator==(const bidirectional_iterator<Tx, Xx> & A,
		const bidirectional_iterator<Ty, Xy> & B)
	{
		if (A.base() == B.base())
			return (true);
		return (false);
	}

	template<typename Tx, typename Xx, typename Ty, typename Xy>
	bool operator!=(const bidirectional_iterator<Tx, Xx> & A,
		const bidirectional_iterator<Ty, Xy> & B)
	{
		if (A.base() != B.base())
			return (true);
		return (false);
	}
}