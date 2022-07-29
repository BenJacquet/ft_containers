/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:37:25 by jabenjam          #+#    #+#             */
/*   Updated: 2022/07/28 17:19:57 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// TESTS PERSO

#include "utils/utils.hpp"
#include "containers/vector.hpp"
#include "containers/stack.hpp"
#include <vector>
#include <stack>

template<typename T>
void vector_status(ft::vector<T> &v)
{
	typename ft::vector<T>::iterator it = v.begin();
	typename ft::vector<T>::iterator ite = v.end();

	COUT_NC("-----------------");
	COUT_NC("size=" << v.size());
	COUT_NC("capacity=" << v.capacity());
	COUT_NC("content:");
	for (int i = 0; it != ite; it++, i++)
		COUT_NC("[" << i << "] - " << *it);
	COUT_NC("-----------------" << std::endl);
}

class Awesome {

	public:

		Awesome( void ) : _n( 42 ) { std::cout << "Default constructor" << std::endl; } //should not happen too often or else there is a wrong use of allocator (which calls the copy constructor)
		Awesome( int n ) : _n( n ) { std::cout << "Int constructor" << std::endl; (void)n; }
		Awesome( Awesome const &rhs ) : _n( 42 ) { *this = rhs;}
		virtual ~Awesome(void) {}

		Awesome &operator=( Awesome const & rhs ) { this->_n = rhs._n; return (*this); }
		bool operator==( Awesome const & rhs ) const { return (this->_n == rhs._n); }
		bool operator!=( Awesome const & rhs ) const { return (this->_n != rhs._n); }
		bool operator>( Awesome const & rhs ) const { return (this->_n > rhs._n); }
		bool operator<( Awesome const & rhs ) const { return (this->_n < rhs._n); }
		bool operator>=( Awesome const & rhs ) const { return (this->_n >= rhs._n); }
		bool operator<=( Awesome const & rhs ) const { return (this->_n <= rhs._n); }
		void operator+=(int rhs){ _n += rhs; }
		int get( void ) const { return this->_n; }

	private:

		int _n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

namespace ft {

template <class T>
void	print_vector(vector<T> &test)
{
	typename vector<T>::iterator		beg = test.begin();
	typename vector<T>::iterator		end = test.end();
	std::cout << "size : " << test.size() << ", capacity : " << test.capacity() << std::endl;
	for (typename vector<T>::iterator it = beg; it != end; it++)
	{
		std::cout << *it << " ";
		if (((it - beg) % 10 == 9) && it > beg)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

template <class T>
void	copy_swap_tests(void)
{
	std::cout << std::endl << "COPY && SWAP TESTS" << std::endl;
	ft::vector<T> test;
	for (size_t i = 0; i < 50; i++) { test.push_back(i); }
	ft::vector<T> test_copy(test);
	for (size_t i = 0; i < test_copy.size(); i++) { test_copy[i] += 100; }
	COUT_NC("TEST0");
	print_vector<T>(test_copy);
	ft::vector<T> test_range(test.begin() + 20, test.begin() + 30);
	print_vector<T>(test_range);
	COUT_NC("TEST1");
	test_copy.swap(test);
	COUT_NC("TEST2");
	print_vector<T>(test);
	print_vector<T>(test_copy);
	COUT_NC("TEST3");
	test_copy.swap(test_range);
	COUT_NC("TEST4");
	print_vector<T>(test_range);
	print_vector<T>(test_copy);
	COUT_NC("TEST5");
	test.swap(test_copy);
	COUT_NC("TEST6");
	print_vector<T>(test);
	print_vector<T>(test_copy);
	COUT_NC("TEST7");
}
}

void	vector_tests()
{
	COUT_NC("---------------------- VECTOR ----------------------");
	COUT_NC("CONSTRUCTOR --- NO_ARG_OVERLOAD");
	ft::vector<int> numbers;
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("INSERT --- SINGLE_ELEMENT_OVERLOAD");
	numbers.insert(numbers.begin(), 1);
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("INSERT --- FILL_OVERLOAD - ADDING TWO");
	numbers.insert(numbers.begin(), 2, 30);
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("INSERT --- FILL_OVERLOAD - ADDING TWO");
	numbers.insert(numbers.begin(), 2, 15);
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("INSERT --- FILL_OVERLOAD - ADDING EIGHT");
	numbers.insert(numbers.begin(), 8, 10);
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("INSERT --- FILL_OVERLOAD ADDING TWO");
	numbers.insert(numbers.begin() + 5, 2, 5);
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("push_back");
	numbers.push_back(45);
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("pop_back");
	numbers.pop_back();
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("FRONT");
	COUT_NC(numbers.front());
	std::cout << std::endl;

	COUT_NC("BACK");
	COUT_NC(numbers.back());
	std::cout << std::endl;

	COUT_NC("AT");
	COUT_NC(numbers.at(13));
	std::cout << std::endl;

	COUT_NC("CONSTRUCTOR --- FILL_OVERLOAD");
	COUT_NC("numbers2");
	ft::vector<int> numbers2(5, 12);
	COUT_NC("numbers2");
	vector_status(numbers2);

	COUT_NC("SWAP");
	numbers2.swap(numbers);
	COUT_NC("numbers");
	vector_status(numbers);
	COUT_NC("numbers2");
	vector_status(numbers2);
	
	COUT_NC("RESIZE --- NO_VALUE --- SIZE_UP");
	numbers2.resize(50);
	vector_status(numbers2);

	COUT_NC("RESIZE --- NO_VALUE --- SIZE_DOWN");
	numbers2.resize(3);
	vector_status(numbers2);

	COUT_NC("RESIZE --- NO_VALUE --- SAME_SIZE");
	numbers2.resize(3);
	vector_status(numbers2);

	COUT_NC("RESIZE --- WITH_VALUE --- SIZE_UP");
	numbers2.resize(30, 20);
	vector_status(numbers2);

	COUT_NC("RESIZE --- WITH_VALUE --- SIZE_DOWN");
	numbers2.assign(5, 5);
	vector_status(numbers2);

	COUT_NC("RESIZE --- WITH_VALUE --- SAME_SIZE");
	numbers2.assign(5, 5);
	vector_status(numbers2);

	COUT_NC("CLEAR");
	numbers2.clear();
	vector_status(numbers2);

	COUT_NC("INSERTING FOR NEXT TESTS");
	for (int i = 0; i < 5; i++)
		numbers2.insert(numbers2.begin() + i, i);
	vector_status(numbers2);

	COUT_NC("ERASE --- RANGE_OVERLOAD");
	numbers2.erase(numbers2.begin(), numbers2.begin() + 1);
	vector_status(numbers2);
	
	COUT_NC("ERASE --- SINGLE_ELEMENT_OVERLOAD");	
	numbers2.erase(numbers2.begin() + 3);
	vector_status(numbers2);

	COUT_NC("NON MEMBER SWAP");
	ft::swap(numbers2, numbers);
	COUT_NC("numbers");
	vector_status(numbers);
	COUT_NC("numbers2");
	vector_status(numbers2);

	COUT_NC("MAZOISE TEST FOR CHECK OF COPY_SWAP");
	ft::copy_swap_tests<Awesome>();

}

void	stack_tests()
{
	COUT_NC("---------------------- STACK ----------------------");
	ft::stack<int> numbers;
	// ft::stack<int, ft::vector<int> > numbers;
	// ft::stack<int, std::deque<int> > numbers;


	COUT_NC("EMPTY --- EMPTY");
	COUT_NC(numbers.empty() << std::endl);

	COUT_NC("SIZE --- EMPTY");
	COUT_NC(numbers.size() << std::endl);

	COUT_NC("PUSH OF FIVE ELEMENTS");
	for (int i = 0; i < 5; i++)
	{
		numbers.push(i);
		COUT_NC("STACK TOP ELEMENT");
		COUT_NC(numbers.top() << std::endl);
	}

	COUT_NC("PUSH");
	numbers.push(5);
	COUT_NC("STACK TOP ELEMENT");
	COUT_NC(numbers.top() << std::endl);

	COUT_NC("SIZE --- NOT EMPTY");
	COUT_NC(numbers.size() << std::endl);

	COUT_NC("EMPTY --- NOT EMPTY");
	COUT_NC(numbers.empty() << std::endl);

	COUT_NC("POP");
	numbers.pop();
	COUT_NC("STACK TOP ELEMENT");
	COUT_NC(numbers.top() << std::endl);

	ft::stack<int> numbers2;
	// ft::stack<int, std::deque<int> > numbers2;

	COUT_NC("OPERATOR=");
	numbers2 = numbers;
	
	COUT_NC("STACK TOP ELEMENT");
	COUT_NC(numbers.top() << std::endl);

	COUT_NC("SIZE --- NOT EMPTY");
	COUT_NC(numbers.size() << std::endl);
}

void	map_tests()
{
	COUT_NC("---------------------- MAP ----------------------");
}

int main()
{
	vector_tests();
	stack_tests();
	// map_tests();
	return (0);
}

// TESTS SUJET

// #include <iostream>
// #include <string>
// #include <deque>
// #if 1 //CREATE A REAL STL EXAMPLE
// 	#include <map>
// 	#include <stack>
// 	#include <vector>
// 	namespace ft = std;
// #else
// 	#include <map.hpp>
// 	#include <stack.hpp>
// 	#include <vector.hpp>
// #endif

// #include <stdlib.h>

// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };

// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template<typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
// 	ft::map<int, int> map_int;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}
	
// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		ft::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;
// 	return (0);
// }