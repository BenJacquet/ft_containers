/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:24:50 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/17 11:31:31 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <limits>
#include "../utils/utils.hpp"
#include "../utils/type_traits.hpp"
#include "../utils/algorithm.hpp"
#include "../iterator/random_access_iterator.hpp"

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef	std::size_t										size_type;
			typedef	std::ptrdiff_t									difference_type;
			typedef T&												reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
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
			{ insert(NULL, n, val); }

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

			virtual ~vector()
			{
				clear();
				if (_capacity > 0 && _base != NULL)
					_allocator.deallocate(_base, _capacity);
			}

			vector& operator=(const vector& rhs)
			{
				if (&rhs != this)
				{
					_allocator = rhs._allocator;
					assign(rhs.begin(), rhs.end());
				}
				return (*this);
			}

			/*
			** ITERATORS
			*/

			iterator begin()
			{ return (iterator(_base[0])); }

			const_iterator begin() const
			{ return (const_iterator(_base[0])); }

			iterator end()
			{ return (iterator(_base[_size])); }

			const_iterator end() const
			{ return (const_iterator(_base[_size])); }

			reverse_iterator rbegin()
			{ return (reverse_iterator(end())); }

			const_reverse_iterator rbegin() const
			{ return (const_reverse_iterator(end())); }

			reverse_iterator rend()
			{ return (reverse_iterator(begin())); }

			const_reverse_iterator rend() const
			{ return (const_reverse_iterator(begin())); }

			/*
			** CAPACITY
			*/

			size_type size() const
			{ return (_size); }
			
			size_type max_size() const
			{ return (_allocator.max_size()); }

			void resize(size_type n, value_type val = value_type())
			{
				if (_size < n)
				{
					insert(end(), n - _size, val);
				}
				else
				{
					while (_size > n)
						erase(end() - 1);
				}
			}

			size_type capacity() const
			{ return (_capacity); }

			bool empty() const
			{ return (_size == 0); }

			void reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (_capacity < n)
				{
					pointer old_mem = _base;
					_base = _allocator.allocate(n);
					if (_capacity)
					{
						for (size_type i = 0; i < _size; i++)
						{
							_allocator.construct(_base + i, old_mem[i]);
							_allocator.destroy(old_mem + i);
						}
					}
					_allocator.deallocate(old_mem, _capacity);
					_capacity = n;
				}
			}

			/*
			** ELEMENT ACCESS
			*/

			reference operator[](size_type n)
			{ return (at(n)); }

			const_reference operator[](size_type n) const
			{ return (at(n)); }

			reference at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("Out of range");
				return (_base[n]);
			}

			const_reference at(size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("Out of range");
				return (_base[n]);
			}

			reference front()
			{ return (_base[0]); }
 
			const_reference front() const
			{ return (_base[0]); }

			reference back()
			{ return (_base[_size - 1]); }

			const_reference back() const
			{ return (_base[_size - 1]); }

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
				resize(len);
				for(int i = 0; first != last; i++, first++)
					_base[i] = *first;
			}
			
			// fill (2) ---
			void assign(size_type n, const value_type& val)
			{
				clear();
				if (n > _capacity)
					reserve(n);
				iterator it = begin();
				for (size_type i(0); i < n ; i++, it++)
					insert(it, val);
			}

			void push_back(const value_type& val)
			{ insert(end(), val); }

			void pop_back()
			{ erase(end() - 1); }

			// single element(1) ---
			iterator insert(iterator position, const value_type& val)
			{
				size_type idx = position - begin();
				insert(position, 1, val);
				return (begin() + idx);
			}

			// fill (2) ---
			void insert(iterator position, size_type n, const value_type& val)
			{
				difference_type	start(position - begin());
				size_type		len(_size - start);
				pointer			tmp(NULL);

				if (!n || n > max_size())
					return ;
				tmp = _allocator.allocate(len);
				if (!_capacity)
					reserve(_size + n);
				else if (_size + n > _size * 2)
					reserve(_size + n);
				else if (_size + n > _capacity)
					reserve(_size * 2);
				for (size_type i(start); i < _size; i++)
				{
					_allocator.construct(tmp + (i - start), _base[i]);
					_allocator.destroy(_base + i);
				}
				for (size_type i(0); i < n; i++)
				{
					_allocator.construct(_base + (i + start), val);
					_size++;
				}
				for (size_type i(0); i < len; i++)
				{
					_allocator.construct(_base + (i + start + n), tmp[i]);
					_allocator.destroy(tmp + i);
				}
				_allocator.deallocate(tmp, len);
			}

			// range (3) ---
			template<class InputIterator>
			void insert(iterator position, InputIterator first,
					typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
			{
				difference_type	start(position - begin());
				size_type		len(_size - start);
				pointer			tmp(NULL);
				size_type		n(0);

				for (; last != first; last--)
					n++;
				if (!n || n > max_size())
					return ;
				tmp = _allocator.allocate(len);
				if (!_capacity)
					reserve(_size + n);
				else if (_size + n > _size * 2)
					reserve(_size + n);
				else if (_size + n > _capacity)
					reserve(_size * 2);
				for (size_type i(start); i < _size; i++)
				{
					_allocator.construct(tmp + (i - start), _base[i]);
					_allocator.destroy(_base + i);
				}
				for (size_type i(0); i < n; i++)
				{
					_allocator.construct(_base + (i + start), *first);
					first++;
					_size++;
				}
				for (size_type i(0); i < len; i++)
				{
					_allocator.construct(_base + (i + start + n), tmp[i]);
					_allocator.destroy(tmp + i);
				}
				_allocator.deallocate(tmp, len);
			}

			// single element (1) ---
			iterator erase(iterator position)
			{ return erase(position, position + 1); }
			
			// range (2) ---
			iterator erase(iterator first, iterator last)
			{
				difference_type size = last - first;
				difference_type index = first - begin();
				difference_type it = index;
				int i = _size - (size + index);

				for (; i; i--, first++, index++)
					_base[index] = _base[index + size];
				for (; size; _size--, size--)
					_allocator.destroy(_base + (_size - 1));
				return iterator(_base + it);
			}

			void swap(vector& rhs)
			{
				pointer tmp = _base;
				size_type tmpsize = _size;
				size_type tmpcapacity = _capacity;
				allocator_type tmpalloc = _allocator;

				_base = rhs._base;
				_size = rhs._size;
				_capacity = rhs._capacity;
				_allocator = rhs._allocator;

				rhs._base = tmp;
				rhs._size = tmpsize;
				rhs._capacity = tmpcapacity;
				rhs._allocator = tmpalloc;
			}

			void clear()
			{ erase(begin(), end()); }

			/*
			** ALLOCATOR
			*/

			allocator_type get_allocator() const
			{ return (_allocator); }

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
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	// (2) ---
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{ return (!(lhs == rhs)); };

	// (3) ---
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); };

	// (4) ---
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (!(rhs < lhs)); };

	// (5) ---
	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (rhs < lhs); };

	// (6) ---
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (!(lhs < rhs)); };

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{ x.swap(y); }
};