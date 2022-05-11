/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:04:45 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/11 16:21:47 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <functional>
#include <memory>

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{
		public:
			typename	Key							key_type;
			typename	T							mapped_type;
			typename	std::pair<const Key, T>		value_type;// remplacer par ft::pair
			typename	usually std::size_t			size_type;
			typename	std::ptrdiff_t				difference_type;
			typename	Compare						key_compare;
			typename	Allocator					allocator_type;
			typename	value_type&					reference;
			typename	const value_type&			const_reference;
			typename	Allocator::pointer			pointer;
			typename	Allocator::const_pointer 	const_pointer;
		// iterator	LegacyBidirectionalIterator to value_type;
		// const_iterator	LegacyBidirectionalIterator to const value_type;
		// reverse_iterator	std::reverse_iterator<iterator>;
		// const_reverse_iterator	std::reverse_iterator<const_iterator>;

			//default (1) ---
			map();

			//comp (2) ---
			explicit map(const Compare& comp,
				const Allocator& alloc = Allocator());

			//iterator (3) ---
			template <class InputIt>
			map(InputIt first, InputIt last,
				const Compare &comp = Compare(),
				const Allocator &alloc = Allocator());

			//copy (4) ---
			map(const map& other);

			~map();

			map& operator=(const map& other);

			allocator_type get_allocator() const;

			T& at(const Key& key);

			const T& at(const Key& key) const;

			T& operator[](const Key& key);

			iterator begin();

			const_iterator begin() const;

			iterator end();

			const_iterator end() const;

			reverse_iterator rbegin();

			const_reverse_iterator rbegin() const;

			reverse_iterator rend();

			const_reverse_iterator rend() const;

			bool empty() const;

			size_type size() const;

			size_type max_size() const;

			void clear();

			pair<iterator, bool> insert(const value_type& value);

			iterator insert(iterator hint, const value_type& value);

			void erase(iterator pos);

			void erase(iterator first, iterator last);

			size_type erase(const Key& key);

			void swap(map& other);

			size_type count(const Key& key) const;

			iterator find(const Key& key);

			const_iterator find(const Key& key) const;

			pair<iterator,iterator> equal_range(const Key& key);

			pair<const_iterator,const_iterator> equal_range(const Key& key) const;

			iterator lower_bound(const Key& key);

			const_iterator lower_bound(const Key& key) const;

			iterator upper_bound(const Key& key);

			const_iterator upper_bound(const Key& key) const;

			key_compare key_comp() const;

			map::value_compare value_comp() const;
	};
	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &lhs,
			  map<Key, T, Compare, Alloc> &rhs);
}