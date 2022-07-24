/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:24:50 by jabenjam          #+#    #+#             */
/*   Updated: 2022/07/24 18:45:33 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../iterator/iterator.hpp"
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
			typedef	std::ptrdiff_t									difference_type;
			typedef	size_t											size_type;
			typedef T&												reference;
			typedef const T&										const_reference;
			typedef typename Alloc::pointer							pointer;
			typedef const typename Alloc::const_pointer				const_pointer;
			typedef ft::random_access_iterator<T>					iterator;
			typedef	ft::random_access_iterator<const T>				const_iterator;
			typedef	ft::reverse_iterator<iterator>					reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;

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
			template <class InputIterator>
			vector (InputIterator first, typename ft::enable_if< !is_integral<InputIterator >::value, InputIterator>::type last,
					const allocator_type& alloc = allocator_type())
			: _allocator(alloc)
			, _base(NULL)
			, _capacity(0)
			, _size(0)
			{ assign(first, last); }

			//copy (4) ---
			vector(const vector& rhs)
			: _base(NULL)
			, _capacity(0)
			, _size(0)
			{ *this = rhs; }

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

			iterator begin()
			{ return(this->_base); }

			const_iterator begin() const
			{ return(this->_base); }

			iterator end()
			{ return(this->_base + this->_size); }

			const_iterator end() const
			{ return(this->_base + this->_size); }

			reverse_iterator rbegin()
			{ return(reverse_iterator(this->end())); }

			const_reverse_iterator rbegin() const
			{ return(const_reverse_iterator(this->end())); }

			reverse_iterator rend()
			{ return(reverse_iterator(this->begin())); }

			const_reverse_iterator rend() const
			{ return(const_reverse_iterator(this->begin())); }

			/*
			** CAPACITY
			*/

			size_type size() const
			{ return(this->_size); }
			
			size_type max_size() const
			{ return(this->_allocator.max_size()); }

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

			size_type capacity() const
			{ return(this->_capacity); }

			bool empty() const
			{ return(this->_size == 0); }

			void reserve(size_type n)
			{
				if (n > this->max_size())
					throw std::length_error("vector::reserve");
				if (n > this->_capacity)
				{
					pointer old_mem = this->_base;
					this->_base = this->_allocator.allocate(n);
					for (size_type i = 0; i < this->_size; i++)
					{
						this->_allocator.construct(this->_base + i, old_mem[i]);
						this->_allocator.destroy(old_mem + i);
					}
					this->_allocator.deallocate(old_mem, this->_capacity);
					this->_capacity = n;
				}
			}

			/*
			** ELEMENT ACCESS
			*/

			reference operator[](size_type n)
			{ return(this->_base[n]); }

			const_reference operator[](size_type n) const
			{ return(this->_base[n]); }

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
			template<class InputIterator>
			void assign(InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
			{
				InputIterator	tmp = first;
				size_type		len = 0;
				while (tmp++ != last)
					len++;
				this->resize(len);
				for(int i = 0; first != last; i++, first++)
					this->_base[i] = *first;
			}
			
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
				difference_type	idx = position - this->begin();
				size_type		i = this->_size;
				int				j = n;
				int				construct = n;
				int				move = this->_size - idx;

				if (this->_size + n > this->_capacity)
				{
					if ((this->_capacity * 2) > (this->_capacity + n))
						reserve(this->_size * 2);
					else
						reserve(this->_capacity + n);
				}
				if (this->_size != 0 && static_cast<unsigned long>(idx) != this->_size)
				{
					for (; construct; construct--)
						this->_allocator.construct(this->_base + i++, T());
					i = this->_size - 1;
					for (; move; move--, i--)
						this->_base[i + n] = this->_base[i] ;
					this->_size += n;
					for (; j; j--, idx++)
						this->_base[idx] = val;
				}
				else
				{
					for (; j; j--, this->_size++)
						this->_allocator.construct((this->_base + this->_size), val);
				}
			}

			// range (3) ---
			template<class InputIterator>
			void insert(iterator position, InputIterator first,
					typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
			{
				difference_type index = position - this->begin();
				difference_type index_tmp = index;
				size_type to_move = this->_size - index;
				size_type i = this->_size - 1;
				size_type size = 0, size_bkp;
				InputIterator tmp = first;

				while (tmp++ != last)
					size++;
				if (size + this->_size > this->_capacity)
				{
					if ((this->_capacity * 2) > (this->_capacity + size))
						reserve(this->_size * 2);
					else
						reserve(this->_capacity + size);
				}
				size_bkp = size;
				for (; size > 0; size--)
					this->_allocator.construct((this->_base + this->_size++), T());
				for (; to_move > 0; to_move--, i--)
					this->_base[i + size_bkp] = this->_base[i] ;
				for (; first != last; first++)
					this->_base[index_tmp++] = *first;
			}

			// single element (1) ---
			iterator erase(iterator position)
			{
				for (iterator it = position; it != this->end() - 1; it++)
					*it = *(it + 1);
				this->_allocator.destroy(&this->_base[this->_size - 1]);
				this->_size--;
				return(position);
			}
			
			// range (2) ---
			iterator erase(iterator first, iterator last)
			{
				size_type	len = last - first;

				for (iterator it = first; it != this->end() - len; it++)
					*it = *(it + len);
				for (iterator it = this->end() - len; it != this->end(); it++)
					this->_allocator.destroy(&(*it));
				this->_size -= len;
				return(first);
			}

			void swap(vector& x)
			{
				pointer			tmp_value;
				size_type			tmp;

				tmp = _capacity;
				_capacity = x._capacity;
				x._capacity = tmp;
				tmp = _size;
				_size = x._size;
				x._size = tmp;
				tmp_value = _base;
				_base = x._value;
				x._value = tmp_value;
			}

			void clear()
			{ erase(this->begin(), this->end()); }

			/*
			** ALLOCATOR
			*/

			allocator_type get_allocator() const
			{ return(this->_allocator); }

	};

	/*
	** Non Member Functions
	*/

	// (1) ---
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	// (2) ---
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{ return (!(lhs == rhs)); };

	// (3) ---
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return(lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); };

	// (4) ---
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return(!(rhs < lhs)); };

	// (5) ---
	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return(rhs < lhs); };

	// (6) ---
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return(!(lhs < rhs)); };

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{ x.swap(y); }
};