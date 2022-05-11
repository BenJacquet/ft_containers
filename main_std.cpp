/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_std.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:37:25 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/11 15:42:40 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// TESTS PERSO

#include "iterator/iterator_traits.hpp"
#include "utils/utils.hpp"
#include "containers/vector.hpp"
#include "containers/stack.hpp"
#include <vector>
#include <stack>

template<typename T>
void vector_status(std::vector<T> &v)
{
	typename std::vector<T>::iterator it = v.begin();
	typename std::vector<T>::iterator ite = v.end();

	COUT_NC("-----------------");
	COUT_NC("size=" << v.size());
	COUT_NC("capacity=" << v.capacity());
	COUT_NC("content:");
	for (int i = 0; it != ite; it++, i++)
		COUT_NC("[" << i << "] - " << *it);
	COUT_NC("-----------------" << std::endl);
}

void	vector_tests()
{
	COUT_NC("---------------------- VECTOR ----------------------");
	COUT_NC("CONSTRUCTOR --- NO_ARG_OVERLOAD");
	std::vector<int> numbers;
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("INSERT --- SINGLE_ELEMENT_OVERLOAD");
	numbers.insert(numbers.begin(), 1);
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("INSERT --- FILL_OVERLOAD");
	numbers.insert(numbers.begin(), 2, 30);
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("INSERT --- FILL_OVERLOAD");
	numbers.insert(numbers.begin(), 2, 15);
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("INSERT --- FILL_OVERLOAD");
	numbers.insert(numbers.begin(), 8, 10);
	COUT_NC("numbers");
	vector_status(numbers);

	COUT_NC("INSERT --- FILL_OVERLOAD");
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

	// COUT_NC((std::enable_if<std::is_integral<std::vector<int>::iterator>::value>));

	COUT_NC("CONSTRUCTOR --- FILL_OVERLOAD");
	COUT_NC("numbers2");
	std::vector<int> numbers2(5, 12);
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
	std::swap(numbers2, numbers);
	COUT_NC("numbers");
	vector_status(numbers);
	COUT_NC("numbers2");
	vector_status(numbers2);
	// std::vector<int>	numbers3(numbers2);

	// numbers2.insert(numbers2.begin(), numbers.begin(), numbers.end());
}

void	stack_tests()
{
	COUT_NC("---------------------- STACK ----------------------");
	std::stack<int, std::vector<int> > numbers;
	// std::stack<int, std::vector<int> > numbers;
	// std::stack<int, std::deque<int> > numbers;


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

	std::stack<int, std::vector<int> > numbers2;

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
	//vector_tests();
	//stack_tests();
	map_tests();
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
// class MutantStack : public std::stack<T>
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

// 	typedef typename std::stack<T>::container_type::iterator iterator;

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

// 	std::vector<std::string> vector_str;
// 	std::vector<int> vector_int;
// 	std::stack<int> stack_int;
// 	std::vector<Buffer> vector_buffer;
// 	std::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
// 	std::map<int, int> map_int;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	std::vector<Buffer>().swap(vector_buffer);

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
// 		map_int.insert(std::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		std::map<int, int> copy = map_int;
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