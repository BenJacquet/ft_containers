/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:32:04 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/16 20:11:04 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"
#include "node.hpp"
#include "pair.hpp"
#include "enums.hpp"
#include <sstream>

namespace ft
{
	template<class T, class Compare = std::less<T>, class Allocator = std::allocator<ft::Node<T> > >
	class RBTree
	{
		public:
			typedef T																		value_type;
			typedef Node<value_type>														node_type;
			typedef Compare																	key_compare;
			typedef Allocator																allocator_type;
			typedef node_type*																pointer;
			typedef	typename ft::bidirectional_iterator<node_type, value_type>				iterator;
			typedef typename ft::bidirectional_iterator<const node_type, const value_type>	const_iterator;
			typedef	size_t																	size_type;
			typedef ft::reverse_iterator<iterator>											reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;

			RBTree(): _alloc(allocator_type()), _comp(key_compare()), _size(0)
			{
				this->_sentry = this->_allocate_node(value_type(), NULL, NULL, E_BLACK);
				this->_root = this->_sentry;
			}

			explicit RBTree(const Compare	&comp, const Allocator &alloc = Allocator()):
				_alloc(alloc), _comp(comp), _size(0)
			{
				this->_sentry = this->_allocate_node(value_type(), NULL, NULL, E_BLACK);
				this->_root = this->_sentry;
			}

			RBTree(const RBTree &copy): _root(NULL), _size(0)
			{
				this->_sentry = this->_allocate_node(value_type(), NULL, NULL, E_BLACK);
				this->_root = this->_sentry;
				*this = copy;
			}

			~RBTree()
			{
				this->clear();
				this->_deallocate_node(this->_sentry);
			}

			RBTree &operator=(const RBTree &other)
			{
				node_type const	*node = NULL;
				if (this != &other)
				{
					this->clear();
					for (const_iterator it = other.begin(); it != other.end(); it++)
					{
						node = it.current;
						this->insert(node->data);
					}
				}
				return (*this);
			}

			/*
			** ITERATORS
			*/

			iterator begin()
			{ return (iterator(this->_minimum(this->root()), this->sentry())); }

			const_iterator begin() const
			{ return (const_iterator(this->_minimum(this->root()), this->sentry())); }
		
			iterator end(void)
			{ return (iterator(this->sentry(), this->sentry())); }

			const_iterator end(void) const
			{ return (const_iterator(this->sentry(), this->sentry())); }

			reverse_iterator rbegin()
			{ return (reverse_iterator(iterator(this->sentry(), this->sentry()))); }

			const_reverse_iterator rbegin() const
			{ return (const_reverse_iterator(const_iterator(this->sentry(), this->sentry()))); }

			reverse_iterator rend()
			{ return (reverse_iterator(iterator(this->_minimum(this->root()), this->sentry()))); }

			const_reverse_iterator rend() const
			{ return (const_reverse_iterator(const_iterator(this->_minimum(this->root()), this->sentry()))); }

			/*
			** CAPACITY
			*/

			size_type size() const
			{ return (this->_size); }

			size_type max_size() const
			{ return (this->_alloc.max_size()); }

			/*
			** MODIFIERS
			*/

			ft::pair<iterator, bool> insert(const value_type &x)
			{
				pointer						node;
				iterator					it = this->search(x);
				ft::pair<iterator, bool>	ret;
				if (it != this->end())
					return (ft::make_pair(iterator(it), 0));
				node = this->_allocate_node(x, this->sentry(), this->sentry(), E_RED);
				ret = this->_insert(this->root(), node);
				if (ret.second == false)
					this->_deallocate_node(node);
				return (ret);
			}

			iterator insert(iterator hint, const value_type &x)
			{
				ft::pair<iterator, bool>	ret;
				pointer						node;
				pointer						current = hint.current;
				pointer						parent = current->parent;
				iterator					it = this->search(x);
				if (it != this->end())
					return (hint);
				node = this->_allocate_node(x, this->sentry(), this->sentry(), E_RED);
				while (parent != NULL && this->_comp(parent->data, x))
				{
					current = current->parent;
					parent = parent->parent;
				}
				if (hint.current == this->sentry() || parent == NULL)
					current = this->root();
				ret = this->_insert(current, node);
				if (ret.second == false)
					this->_deallocate_node(node);
				return (ret.first);
			}

			void erase(iterator position)
			{
				if (position != this->end())
					this->_erase(position.current);
			}

			size_type erase(const value_type &key)
			{
				iterator	it = this->search(key);

				if (it == this->end())
					return (0);
				this->_erase(it.current);
				return (1);
			}

			void clear()
			{
				while (this->root() != this->sentry())
					this->_erase(this->root());
			}

			void swap(RBTree &x)
			{
				std::swap(this->_root, x._root);
				std::swap(this->_sentry, x._sentry);
				std::swap(this->_size, x._size);
			}

			/*
			** LOOKUP
			*/

			iterator search(const value_type &x)
			{
				return (this->_search(this->root(), x));
			}

			const_iterator search(const value_type &x) const
			{
				const_iterator	it = this->_search(this->root(), x);
				return (it);
			}

			iterator lower_bound(const value_type &x)
			{
				for (iterator it = this->begin(); it != this->end(); it++)
					if (!(this->_comp(it.current->data, x)))
						return (it);
				return (this->end());
			}

			const_iterator lower_bound(const value_type &x) const
			{
				for (const_iterator it = this->begin(); it != this->end(); it++)
					if (!(this->_comp(it.current->data, x)))
						return (it);
				return (this->end());
			}

			iterator upper_bound(const value_type &x)
			{
				for (iterator it = this->begin(); it != this->end(); it++)
					if (!(this->_comp(it.current->data, x)) && this->_comp(x, it.current->data))
						return (it);
				return (this->end());
			}

			const_iterator upper_bound(const value_type &x) const
			{
				for (const_iterator it = this->begin(); it != this->end(); it++)
					if (!(this->_comp(it.current->data, x)) && this->_comp(x, it.current->data))
						return (it);
				return (this->end());
			}

			ft::pair<iterator, iterator> equal_range(const value_type &x)
			{
				ft::pair<iterator, iterator>	range;
				range.first = this->lower_bound(x);
				range.second = this->upper_bound(x);
				return (range);
			}

			ft::pair<const_iterator, const_iterator> equal_range(const value_type &x) const
			{
				ft::pair<const_iterator, const_iterator>	range;
				range.first = this->lower_bound(x);
				range.second = this->upper_bound(x);
				return (range);
			}

			/*
			** OBSERVERS
			*/

			pointer	root(void) const
			{ return (this->_root); }

			pointer	sentry(void) const
			{ return (this->_sentry); }

			/*
			** DISPLAY FUNCTIONS
			*/

			void display(pointer node)
			{
				std::stringstream	buffer;
				std::cout << "size: " << this->size() << std::endl;
				if (node != this->sentry())
				{
					this->_display(node, buffer, true, "");
					std::cout << buffer.str();
				}
			}

			void display(void)
			{
				std::stringstream	buffer;
				std::cout <<  "size: " << this->size() << std::endl;
				if (this->root() != this->sentry())
				{
					this->_display(this->root(), buffer, true, "");
					std::cout << buffer.str();
				}
			}

		private:
			pointer						_root;
			pointer						_sentry;
			allocator_type				_alloc;
			key_compare					_comp;
			size_type					_size;

			pointer	_allocate_node(const value_type &x, pointer left, pointer right, bool color)
			{
				pointer	node = this->_alloc.allocate(1);
				this->_alloc.construct(node, x);
				node->left = left;
				node->right = right;
				node->color = color;
				return (node);
			}

			void _deallocate_node(pointer node)
			{
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
			}

			void _relocate_sentry(void)
			{
				if (this->sentry() != this->root())
					this->_sentry->parent = this->root();
				else
					this->_sentry->parent = NULL;
			}


			ft::pair<iterator, bool> _insert(pointer current, pointer node)
			{
				pointer	parent = NULL;
				while (current != this->sentry())
				{
					parent = current;
					if (this->_comp(node->data, current->data))
						current = current->left;
					else if (this->_comp(current->data, node->data))
						current = current->right;
					else
						return (ft::make_pair(current, false));
				}
				this->_size++;
				node->parent = parent;
				if (parent == NULL)
					this->_root = node;
				else if (this->_comp(node->data, parent->data))
					parent->left = node;
				else
					parent->right = node;
				if (node->parent == NULL)
				{
					node->color = E_BLACK;
					this->_relocate_sentry();
					return (ft::make_pair(node, true));
				}
				if (node->parent->parent == NULL)
				{
					this->_relocate_sentry();
					return (ft::make_pair(node, true));
				}
				this->_rebalance_insert(node);
				this->_relocate_sentry();
				return (ft::make_pair(node, true));
			}

			void _rebalance_insert(pointer node)
			{
				pointer	uncle = NULL;
				while (node->parent->color == E_RED)
				{
					if (node->parent == node->parent->parent->right)
					{
						uncle = node->parent->parent->left;
						if (uncle->color == E_RED)
						{
							uncle->color = E_BLACK;
							node->parent->color = E_BLACK;
							node->parent->parent->color = E_RED;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->left)
							{
								node = node->parent;
								this->_rightRotate(node);
							}
							node->parent->color = E_BLACK;
							node->parent->parent->color = E_RED;
							this->_leftRotate(node->parent->parent);
						}
					}
					else
					{
						uncle = node->parent->parent->right;
						if (uncle->color == E_RED)
						{
							uncle->color = E_BLACK;
							node->parent->color = E_BLACK;
							node->parent->parent->color = E_RED;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->right)
							{
								node = node->parent;
								this->_leftRotate(node);
							}
							node->parent->color = E_BLACK;
							node->parent->parent->color = E_RED;
							this->_rightRotate(node->parent->parent);
						}
					}
					if (node == this->root())
						break;
				}
				this->_root->color = E_BLACK;
			}

			void _erase(pointer node)
			{
				pointer		x;
				pointer		y = node;
				bool		originalColor = node->color;
				if (node->left == this->sentry())
				{
					x = node->right;
					this->_switch_nodes(node, node->right);
				}
				else if (node->right == this->sentry())
				{
					x = node->left;
					this->_switch_nodes(node, node->left);
				}
				else
				{
					y = this->_minimum(node->right);
					originalColor = y->color;
					x = y->right;
					if (y->parent == node)
						x->parent = y;
					else
					{
						this->_switch_nodes(y, y->right);
						y->right = node->right;
						y->right->parent = y;
					}
					this->_switch_nodes(node, y);
					y->left = node->left;
					y->left->parent = y;
					y->color = node->color;
				}
				this->_deallocate_node(node);
				if (originalColor == E_BLACK)
					this->_rebalance_erase(x);
				this->_size--;
				this->_relocate_sentry();
			}

			void _rebalance_erase(pointer node)
			{
				pointer	uncle;
				while (node != this->root() && node->color == E_BLACK)
				{
					if (node == node->parent->left)
					{
						uncle = node->parent->right;
						if (uncle->color == E_RED)
						{
							uncle->color = E_BLACK;
							node->parent->color = E_RED;
							this->_leftRotate(node->parent);
							uncle = node->parent->right;
						}
						if (uncle->left->color == E_BLACK && uncle->right->color == E_BLACK)
						{
							uncle->color = E_RED;
							node = node->parent;
						}
						else
						{
							if (uncle->right->color == E_BLACK)
							{
								uncle->left->color = E_BLACK;
								uncle->color = E_RED;
								this->_rightRotate(uncle);
								uncle = node->parent->right;
							}
							uncle->color = node->parent->color;
							node->parent->color = E_BLACK;
							uncle->right->color = E_BLACK;
							this->_leftRotate(node->parent);
							node = this->root();
						}
					}
					else
					{
						uncle = node->parent->left;
						if (uncle->color == E_RED)
						{
							uncle->color = E_BLACK;
							node->parent->color = E_RED;
							this->_rightRotate(node->parent);
							uncle = node->parent->left;
						}
						if (uncle->right->color == E_BLACK && uncle->left->color == E_BLACK)
						{
							uncle->color = E_RED;
							node = node->parent;
						}
						else
						{
							if (uncle->left->color == E_BLACK)
							{
								uncle->right->color = E_BLACK;
								uncle->color = E_RED;
								this->_leftRotate(uncle);
								uncle = node->parent->left;
							}
							uncle->color = node->parent->color;
							node->parent->color = E_BLACK;
							uncle->left->color = E_BLACK;
							this->_rightRotate(node->parent);
							node = this->root();
						}
					}
				}
				node->color = E_BLACK;
			}

			void _switch_nodes(pointer node, pointer replacement)
			{
				if (node->parent == NULL)
					this->_root = replacement;
				else if (node == node->parent->left)
					node->parent->left = replacement;
				else
					node->parent->right = replacement;
				replacement->parent = node->parent;
			}

			void _leftRotate(pointer node)
			{
				pointer	child = node->right;
				node->right = child->left;
				if (child->left != this->sentry())
					child->left->parent = node;
				child->parent = node->parent;
				if (node->parent == NULL)
					this->_root = child;
				else if (node == node->parent->left)
					node->parent->left = child;
				else
					node->parent->right = child;
				child->left = node;
				node->parent = child;
			}

			void _rightRotate(pointer node)
			{
				pointer	child = node->left;
				node->left = child->right;
				if (child->right != this->sentry())
					child->right->parent = node;
				child->parent = node->parent;
				if (node->parent == NULL)
					this->_root = child;
				else if (node == node->parent->right)
					node->parent->right = child;
				else
					node->parent->left = child;
				child->right = node;
				node->parent = child;
			}

			iterator _search(const pointer node, const value_type &x)
			{
				pointer	current = node;
				while (current != this->sentry())
				{
					if (this->_comp(x, current->data))
						current = current->left;
					else if (this->_comp(current->data, x))
						current = current->right;
					else
						return (current);
				}
				return (this->end());
			}

			const_iterator _search(const pointer node, const value_type &x) const
			{
				pointer	current = node;
				while (current != this->sentry())
				{
					if (this->_comp(x, current->data))
						current = current->left;
					else if (this->_comp(current->data, x))
						current = current->right;
					else
						return (current);
				}
				return (this->end());
			}

			pointer _minimum(pointer node)
			{
				pointer	current = node;
				if (current != this->sentry())
				{
					while (current->left != this->sentry())
						current = current->left;
				}
				return (current);
			}

			pointer _minimum(pointer node) const
			{
				pointer	current = node;
				if (current != this->sentry())
				{
					while (current->left != this->sentry())
						current = current->left;
				}
				return (current);
			}

			pointer _maximum(pointer node)
			{
				pointer	current = node;
				if (current != this->sentry())
				{
					while (current->right != this->sentry())
						current = current->right;
				}
				return (current);
			}

			pointer _maximum(pointer node) const
			{
				pointer	current = node;
				if (current != this->sentry())
				{
					while (current->right != this->sentry())
						current = current->right;
				}
				return (current);
			}

			void _display(pointer node, std::stringstream &buffer, bool isTail, std::string prefix)
			{
				if (node->right != this->sentry())
					this->_display(node->right, buffer, false, std::string(prefix).append(isTail ? "│   " : "    "));
				buffer << prefix << (isTail ? "└── " : "┌── ");
				if (node->color == E_RED)
					buffer << "\033[31m";
				buffer << node->data << "\033[0m" << std::endl;
				if (node->left != this->sentry())
					this->_display(node->left, buffer, true, std::string(prefix).append(isTail ? "    " : "│   "));
			}
		};
}