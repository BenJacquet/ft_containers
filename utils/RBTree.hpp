/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:05:45 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/17 11:53:18 by jabenjam         ###   ########.fr       */
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

	template<typename value_type, typename key_type, typename Compare = std::less<key_type>,
			typename Alloc = std::allocator<node<value_type> > >
	class RBTree
	{
		public:
			typedef node<value_type> node_type;

			class value_compare : public std::binary_function<value_type, value_type, bool>
				{
					friend class RBTree;
					protected :
						Compare _comp;
						value_compare(Compare c) : _comp(c) {} // constructed with map's comparison object
					public :
						typedef bool	result_type;
						typedef value_type	first_argument_type;
						typedef value_type	second_argument_type;

						bool operator() (const value_type& x, const value_type& y) const
						{
							return _comp(x.first , y.first);
						}
				};

		public:
			RBTree(const Compare &comp = Compare(),
						const Alloc &alloc = Alloc())
						: _comp(comp), _alloc(alloc), _size(0)
			{
				this->_sentinel = this->_alloc.allocate(1);
				this->_alloc.construct(this->_sentinel, value_type());
				this->_sentinel->parent = NULL;
				this->_sentinel->left = NULL;
				this->_sentinel->right = NULL;
				this->_sentinel->color = E_BLACK;
				this->_root = this->_sentinel;
			}

			virtual ~RBTree()
			{
				this->destroy_tree();
				this->_alloc.destroy(this->_sentinel);
				this->_alloc.deallocate(this->_sentinel, 1);
			}

			RBTree & operator=(const RBTree & x)
			{
				if (this != &x)
				{
					this->destroy_tree();
					node_type * node = x.minimum(x._root);
					while (node != x._sentinel)
					{
						this->insert(node->key_val);
						node = x.found_next_one(node);
					}
				}
				return (*this);
			}

			void swap(RBTree &x)
			{
				std::swap(this->_root, x._root);
				std::swap(this->_sentinel, x._sentinel);
				std::swap(this->_size, x._size);
			}

			node<value_type>*
			init_node(node<value_type> *to_init, node<value_type> *parent, node<value_type> *left,
					  node<value_type> *right, const value_type &val, int color = E_RED)
			{
				to_init = this->_alloc.allocate(1);
				this->_alloc.construct(to_init, val);
				to_init->parent = parent;
				to_init->left = left;
				to_init->right = right;
				to_init->color = color;
				return to_init;
			}

			void destroy_tree()
			{
				if (this->_size == 0)
					return ;
				node<value_type> *it = this->minimum(this->_root);
				while (this->_size > 0)
				{
					this->erase(it);
					if (this->_size > 0)
						it = this->minimum(this->_root);
				}
				this->_root = this->_sentinel;
			}

			size_t max_size() const
			{ return this->_alloc.max_size(); }

			node<value_type>* minimum(node<value_type> *node) const
			{
				while (node->left != this->_sentinel && node != this->_sentinel)
					node = node->left;
				return node;
			}

			node<value_type>* maximum(node<value_type> *node) const
			{
				while (node->right != this->_sentinel && node != this->_sentinel)
					node = node->right;
				return node;
			}

			node<value_type>* found_next_one(node<value_type> *node) const
			{
				if (node == maximum(this->_root) || node == this->_sentinel)
						return this->_sentinel;
				if (node->right != this->_sentinel)
					return (minimum(node->right));
				if (node != node->parent->left)
				{
					while (node != node->parent->left)
						node = node->parent;
				}
				node = node->parent;
				return node;
			}

			node<value_type>* found_prec(node<value_type> *node)
			{
				if (node == this->_sentinel)
					return (maximum(this->_root));
				if (node == minimum(this->_root))
					return this->_sentinel;
				if (node->left != this->_sentinel)
					return (maximum(node->left));
				if (node != node->parent->right)
				{
					while (node != node->parent->right)
						node = node->parent;
				}
				node = node->parent;
				return node;
			}

			/*
			**	x = old parent && y = new parent
			*/
			void left_rotate(node<value_type> *x, node<value_type> *y)
			{
				if (x->parent == this->_sentinel)
					this->_root = y;
				if (y->left != this->_sentinel)
				{
					x->right = y->left;
					x->right->parent = x;
				}
				else
					x->right = this->_sentinel;
				y->parent = x->parent;
				if (x->parent != this->_sentinel)
				{
					if (x->parent->left == x)
						x->parent->left = y;
					else
						x->parent->right = y;
				}
				x->parent = y;
				y->left = x;
			}

			void right_rotate(node<value_type> *new_p, node<value_type> *old_p)
			{
				if (old_p->parent == this->_sentinel)
					this->_root = new_p;
				if (new_p->right != this->_sentinel)
				{
					old_p->left = new_p->right;
					old_p->left->parent = old_p;
				}
				else
					old_p->left = this->_sentinel;
				new_p->parent = old_p->parent;
				if (old_p->parent != this->_sentinel)
				{
					if (old_p->parent->left == old_p)
						old_p->parent->left = new_p;
					else
						old_p->parent->right = new_p;
				}
				old_p->parent = new_p;
				new_p->right = old_p;
			}

			node<value_type>* insert(const value_type& ins)
			{
				node<value_type> *to_move = this->_root;
				node<value_type> *to_ins = NULL;
				if (this->_size == 0)
				{
					to_ins = this->init_node(to_ins, this->_sentinel, this->_sentinel,
						this->_sentinel, ins, E_BLACK);
					this->_root = to_ins;
					this->_size++;
					return (this->_root);
				}
				else
					return (insert2(ins, to_move, to_ins));
			}

			/*
			** Try to insert in the tree.
			*/
			node<value_type>* insert2(const value_type& ins, node<value_type> *to_move, node<value_type> *to_ins)
			{
				if (this->_comp(ins, to_move->key_val)) /* if key of ins < key of to_move */
				{
					if (to_move->left == this->_sentinel)
					{
						to_ins = this->init_node(to_ins, to_move, this->_sentinel,
							this->_sentinel, ins, E_RED);
						to_move->left = to_ins;
						this->_size++;
						to_move = to_ins;
						rb_tree_post_insert(to_ins);
						return to_move;
					}
					else
					{
						to_move = to_move->left;
						return insert2(ins, to_move, to_ins);
					}
				}
				else if (!(this->_comp(ins, to_move->key_val)) &&
						 !(this->_comp(to_move->key_val, ins))) /* if equal the new insert is ignoE_red */
					return to_move;
				else
				{
					if (to_move->right == this->_sentinel)
					{
						to_ins = this->init_node(to_ins, to_move, this->_sentinel,
							this->_sentinel, ins, E_RED);
						to_move->right = to_ins;
						this->_size++;
						to_move = to_ins;
						rb_tree_post_insert(to_ins);
						return to_move;
					}
					else
					{
						to_move = to_move->right;
						return insert2(ins, to_move, to_ins);
					}
				}
			}

			void rb_tree_post_insert(node<value_type> *z)
			{
				node<value_type> *z_gp = z->parent->parent;
				node<value_type> *z_p = z->parent;
				while (z_p->color == E_RED)
				{
					if (z_p == z_gp->left)
					{
						if (z_gp->right->color == E_RED)
						{
							z_gp->right->color = E_BLACK;
							z_gp->left->color = E_BLACK;
							z_gp->color = E_RED;
							z = z_gp;
						}
						else if (z == z_p->right)
						{
							left_rotate(z_p, z);
							z = z_p;
						}
						else
						{
							z_p->color = E_BLACK;
							z_gp->color = E_RED;
							right_rotate(z_p, z_gp);
						}
					}
					else
					{
						if (z_gp->left->color == E_RED)
						{
							z_gp->left->color = E_BLACK;
							z_gp->right->color = E_BLACK;
							z_gp->color = E_RED;
							z = z_gp;
						}
						else if (z == z_p->left)
						{
							right_rotate(z, z_p);
							z = z_p;
						}
						else
						{
							z_p->color = E_BLACK;
							z_gp->color = E_RED;
							left_rotate(z_gp, z_p); 
						}
					}
					z_p = z->parent;
					z_gp = z->parent->parent;
				}
				this->_root->color = E_BLACK;
			}

			void	erase(node<value_type> *z)
			{
				node<value_type> *y = z;
				node<value_type> *x;

				if (this->_size == 0)
					return ;
				int color = z->color;
				if (z->left == this->_sentinel) // No child on the left is found
				{
					x = z->right;
					switch_nodes(z, z->right);
				}
				else if (z->right == this->_sentinel) // No child on the right is found
				{
					x = z->left;
					switch_nodes(z, z->left);
				}
				else  // A child on both sides
				{
					y = minimum(z->right);
					color = y->color;
					x = y->right;
					if (y->parent == z) // If y is z's right child
						x->parent = y;
					else
					{
						switch_nodes(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}

					switch_nodes(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				this->_alloc.deallocate(z, 1);
				this->_size--;
				if (color == E_BLACK)
					rb_tree_post_erase(x);
			}

			void	rb_tree_post_erase(node<value_type> *x)
			{
				node<value_type> *sibling;
				while (x != this->_root && x->color == E_BLACK)
				{
					if (x == x->parent->left)
					{
						sibling = x->parent->right;
						if (sibling->color == E_RED)
						{
							sibling->color = E_BLACK;
							x->parent->color = E_RED;
							left_rotate(x->parent, x->parent->right);
							sibling = x->parent->right;
						}
						if (sibling->left->color == E_BLACK && sibling->right->color == E_BLACK)
						{
							sibling->color = E_RED;
							x = x->parent;
						}
						else
						{
							if (sibling->right->color == E_BLACK)
							{
								sibling->left->color = E_BLACK;
								sibling->color = E_RED;
								right_rotate(sibling->left, sibling);
								sibling = x->parent->right;
							}
							sibling->color = x->parent->color;
							x->parent->color = E_BLACK;
							sibling->right->color = E_BLACK;
							left_rotate(x->parent, x->parent->right);
							x = this->_root;
						}
					}
					else
					{
						sibling = x->parent->left;
						if (sibling->color == E_RED)
						{
							sibling->color = E_BLACK;
							x->parent->color = E_RED;
							right_rotate(x->parent->left, x->parent);
							sibling = x->parent->left;
						}
						if (sibling->right->color == E_BLACK && sibling->left->color == E_BLACK)
						{
							sibling->color = E_RED;
							x = x->parent;
						}
						else
						{
							if (sibling->left->color == E_BLACK)
							{
								sibling->right->color = E_BLACK;
								sibling->color = E_RED;
								left_rotate(sibling, sibling->right);
								sibling = x->parent->left;
							}
							sibling->color = x->parent->color;
							x->parent->color = E_BLACK;
							sibling->left->color = E_BLACK;
							right_rotate(x->parent->left, x->parent);
							x = this->_root;
						}
					}
				}
				x->color = E_BLACK;
			}

			void switch_nodes(node<value_type> *u, node<value_type> *v)
			{
				if (u->parent == this->_sentinel)
					this->_root = v;
				else if (u  == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			size_t size() const
			{ return this->_size; }

			node<value_type> *root() const
			{ return this->_root; }

			node<value_type> *sentinel() const
			{ return this->_sentinel; }

		private:
			value_compare			_comp;
			Alloc					_alloc;
			size_t					_size;
			node<value_type>		*_root;
			node<value_type>		*_sentinel; // empty node used for all leaves to point to, that avoids a ton of null pointers
	};
}