/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:24:50 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/05 13:57:36 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../iterator/random_access_iterator.hpp"
#include "../utils/type_traits.hpp"
#include "../utils/algorithm.hpp"
#include <memory>
#include <stdexcept>

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef T&												reference;
			typedef const T&										const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename ft::random_access_iterator<T>			iterator;
			typedef	typename ft::random_access_iterator<const T>	const_iterator;
			//typedef	reverse_iterator<iterator>					reverse_iterator;
			//typedef	reverse_iterator<const iterator>			const_reverse_iterator;
			typedef	ptrdiff_t										difference_type;
			typedef	size_t											size_type;

		private:
			allocator_type	_allocator;
			pointer			_base;
			size_type		_capacity;
			size_type		_size;

		public:
			//default (1) ---
			explicit vector(const allocator_type& alloc = allocator_type())
			: _allocator(alloc)
			, _base(NULL)
			, _capacity(0)
			, _size(0)
			{}

			//fill (2) ---
			explicit vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
			: _allocator(alloc)
			, _base(NULL)
			, _capacity(0)
			, _size(0)
			{ this->insert(NULL, n, val); }

			//range (3) ---
			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last,
			// 		const allocator_type& alloc = allocator_type());

			//copy (4) ---
			vector(const vector& rhs)
			{
				if (*this != rhs)
					*this = rhs;
			}

			~vector()
			{
				this->clear();
				if (this->_size >= 0 && this->_base != NULL)
					this->_allocator.deallocate(this->_base, this->_capacity); 
			}

			vector& operator=(const vector& rhs)
			{
				this->clear();
				this->_capacity = rhs.capacity();
				this->_allocator = rhs.get_allocator();
				this->insert(this->begin(), rhs.begin(), rhs.end());
				return (*this);
			}

			/*
			** ITERATORS
			*/

			iterator begin() { return(this->_base); }

			const_iterator begin() const { return(this->_base); }

			iterator end() { return(this->_base + this->_size); }

			const_iterator end() const { return(this->_base + this->_size); }

			//reverse_iterator rbegin();

			//const reverse_iterator rbegin() const;

			//reverse_iterator rend();

			//const reverse_iterator rend() const;

			/*
			** CAPACITY
			*/

			size_type size() const { return(this->_size); }
			
			size_type max_size() const { return(this->_allocator.max_size()); }

			void resize(size_type n, value_type val = value_type())
			{
				if (n < this->_size)
				{
					for (; this->_size > n ; this->_size--)
						this->_allocator.destroy(this->_base + n);
				}
				else if (n > this->_size)
				{
					if (n > this->_capacity)
						this->reserve(n);
					for (; this->_size < n; this->_size++)
						this->_base[this->_size] = val;
				}
			}

			size_type capacity() const { return(this->_capacity); }

			bool empty() const { return(this->_size == 0); }

			void reserve(size_type n)
			{
				if (n > this->max_size())
					throw std::length_error("vector::reserve");
				if (n >= this->_capacity)
				{
					pointer old_mem = this->_base;
					pointer new_mem = this->_allocator.allocate(n);
					for (size_type i = 0; i < this->_size; i++)
					{
						this->_allocator.construct(new_mem + i, old_mem[i]);
						new_mem[i] = old_mem[i];
						this->_allocator.destroy(old_mem + i);
					}
					this->_base = new_mem;
					this->_allocator.deallocate(old_mem, this->_capacity);
					this->_capacity = n;
				}
			}

			/*
			** ELEMENT ACCESS
			*/

			reference operator[](size_type n) { return(this->_base[n]); }

			const_reference operator[](size_type n) const { return(this->_base[n]); }

			reference at(size_type n)
			{
				if (n >= this->_size)
					throw std::out_of_range("Out of range");
				return(*(this->begin() + n));
			}

			const_reference at(size_type n) const
			{
				if (n >= this->_size)
					throw std::out_of_range("Out of range");
				return(*(this->begin() + n));
			}

			reference front()
			{ return(*this->begin()); }
 
			const_reference front() const
			{ return(*this->begin()); }

			reference back()
			{ return(*(this->end() - 1)); }

			const_reference back() const
			{ return(*(this->end() - 1)); }

			/*
			** MODIFIERS
			*/

			// range (1) ---
			// template<class InputIterator>
			// void assign(InputIterator first, InputIterator last);
			
			// fill (2) ---
			void assign(size_type n, const value_type& val)
			{
				this->resize(0);
				this->resize(n, val);
			}

			void push_back(const value_type& val)
			{ this->insert(this->end(), val); }

			void pop_back()
			{
				if (this->_size > 0)
				{
					this->_allocator.destroy(this->_base + this->_size - 1);
					this->_size--;
				}
			}

			// single element(1) ---
			iterator insert(iterator position, const value_type& val)
			{
				size_type idx = position - this->begin();
				this->insert(position, 1, val);
				return(iterator(this->_base + idx));
			}

			// fill (2) ---
			void insert(iterator position, size_type n, const value_type& val)
			{
				size_type idx = position - this->begin();
				if (this->_size + n > this->_capacity)
				{
					if (this->_size + n > this->_capacity * 2)
						this->reserve(this->_size + n);
					else
						this->reserve(this->_capacity * 2);
				}
				if (this->_size == 0)
				{
					for (size_type i = 0; i < n; i++)
					{
						this->_allocator.construct(this->_base + i, val);
						this->_size++;
					}
				}
				else
				{
					size_type i = this->_size - 1 + n;
					for (; i >= idx + n; i--)
					{
						this->_base[i] = this->_base[i - n];
						if (i == 0)
							break;
					}
					for (; i >= idx ; i--)
					{
						this->_base[i] = val;
						this->_size++;
						if (i == 0)
							break;
					}
				}
			}

			// range (3) ---
			template<class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last)
			{
				size_type idx = position - this->begin();
				size_type to_copy = last - first;
				COUT(WHITE, "to_copy=" << to_copy);
				COUT(WHITE, "idx=" << idx);
			}


			// single element (1) ---
			iterator erase(iterator position)
			{
				size_type idx = position - this->begin();
				size_type backup = idx;

				this->_allocator.destroy(this->_base + idx);
				for (; idx < this->_size - 1; idx++)
					this->_base[idx] = this->_base[idx + 1];
				this->_size--;
				return(iterator(this->_base + backup));
			}
			
			// range (2) ---
			iterator erase(iterator first, iterator last)
			{
				size_type idx = first - this->begin();
				size_type end = last - this->begin();
				size_type backup = idx;

				for (; idx < end; idx++)
					this->_allocator.destroy(this->_base + idx);
				for (idx = backup; idx < this->_size - (end - backup); idx++)
					this->_base[idx] = this->_base[idx + end];
				this->_size -= end - backup;
				return(iterator(this->_base + backup));
			}

			void swap(vector& x)
			{
				size_type capacity = this->_capacity;
				size_type size = this->_size;
				pointer base = this->_base;
				allocator_type allocator = this->_allocator;

				this->_capacity = x._capacity;
				this->_size = x._size;
				this->_base = x._base;
				this->_allocator = x._allocator;

				x._capacity = capacity;
				x._size = size;
				x._base = base;
				x._allocator = allocator;
			}

			void clear()
			{
				if (this->_capacity >= 0)
					this->_allocator.destroy(this->_base);
				this->_size = 0;
			}

			/*
			** ALLOCATOR
			*/

			allocator_type get_allocator() const
			{ return(this->_allocator); }

	};
	/*
	** NON MEMBER FUNCTION OVERLOADS
	*/

	// (1) ---
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		else if (equal(lhs.begin(), lhs.end(), rhs.begin()))
			return (true);
		return (false);
	};

	// (2) ---
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	};

	// (3) ---
	// template <class T, class Alloc>
	//   bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// (4) ---
	// template <class T, class Alloc>
	//   bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// (5) ---
	// template <class T, class Alloc>
	//   bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// (6) ---
	// template <class T, class Alloc>
	//   bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// template <class T, class Alloc>
	// void swap(vector<T,Alloc>& x, vector<T,Alloc>& y);
};