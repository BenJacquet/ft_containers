/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:24:14 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/13 17:47:32 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"
#include "../utils/utils.hpp"
#include "../utils/node.hpp"

	/*
	** BIDIRECTIONAL ITERATOR (FOR MAP)
	*/

namespace ft 
{
	template <class T>
	class bidirectional_iterator : public iterator<bidirectional_iterator_tag, T>
	{
		public:
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef bidirectional_iterator_tag		iterator_category;

			bidirectional_iterator()
			: _n(0)
			{}

			bidirectional_iterator(node<value_type> *n)
			: _n(n)
			{}

			bidirectional_iterator(const bidirectional_iterator& it)
			: _n(it._n)
			{}

			virtual ~bidirectional_iterator()
			{}

			operator bidirectional_iterator<const T>() const
			{ return bidirectional_iterator<const T>(reinterpret_cast<node<const value_type> *>(this->_n)); }

			reference	operator*()
			{ return ( *(this->_n->get_value())); }

			pointer	operator->()
			{ return ( this->_n->get_value()); }

			bool	operator==(const bidirectional_iterator& rhs) const
			{ return (this->_n == rhs._n); }

			bool	operator!=(const bidirectional_iterator& rhs) const
			{ return (this->_n != rhs._n); }

			bidirectional_iterator& operator++()
			{
				this->_n = this->_get_nearest(E_RIGHT);
				return (*this);
			}

			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator tmp = *this;
				(*this)++;
				return (tmp);
			}

			bidirectional_iterator& operator--()
			{
				this->_n = this->_get_nearest(E_LEFT);
				return (*this);
			}

			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator tmp = *this;
				(*this)--;
				return (tmp);
			}

		private:
			node<value_type>	*_n;

			/**
			 * @brief Returns a pointer to the nearest node according to the direction provided as argument
			 * 
			 * @param direction false/0 = left, true/1 = right
			 * @return node<value_type>* 
			 */
			node<value_type>	*_get_nearest(bool direction) const
			{
				node<value_type> *found = this->_n;

				if (!found)
					return (NULL);
				if (found->get_child(direction) && !found->get_child(direction)->empty())
				{
					found = found->get_child(direction);
					while (found->get_child(!direction) && !found->get_child(!direction)->empty())
						found = found->get_child(!direction);
					return (found);
				}
				else if (found->get_parent())
				{
					if (found->get_direction() != direction)
						return (found->get_parent());
					else
					{
						while (found->get_parent() && found->get_direction() == direction)
							found = found->get_parent();
						if (!found->get_parent())
							return (this->_n->get_child(direction));
						return (found->get_parent());
					}
				}
				else
					return (this->_n->get_child(direction));
			}
	};
}