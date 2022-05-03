/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:37:25 by jabenjam          #+#    #+#             */
/*   Updated: 2022/05/03 17:59:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// TESTS PERSO

#include "iterator/iterator_traits.hpp"
#include "utils/utils.hpp"
#include "vector/vector.hpp"
#include <vector>

template<typename T>
void vector_status(ft::vector<T> &v)
{
	typename ft::vector<T>::iterator it = v.begin();
	typename ft::vector<T>::iterator ite = v.end();

	COUT(WHITE, "-----------------");
	COUT(WHITE, "begin=" << &(*v.begin()));
	COUT(WHITE, "end=" << &(*v.end()));
	COUT(WHITE, "size=" << v.size());
	COUT(WHITE, "capacity=" << v.capacity());
	COUT(WHITE, "content:");
	for (int i = 0; it != ite; it++, i++)
		COUT(WHITE, "[" << i << "] - " << *it);
	COUT(WHITE, "-----------------");
}

int main()
{
	ft::vector<int> numbers;

	COUT(BLUE, "numbers");
	vector_status(numbers);
	numbers.insert(numbers.begin(), 2, 30);
	COUT(BLUE, "numbers");
	vector_status(numbers);
	numbers.insert(numbers.begin(), 2, 15);
	COUT(BLUE, "numbers");
	vector_status(numbers);
	numbers.insert(numbers.begin(), 8, 10);
	COUT(BLUE, "numbers");
	vector_status(numbers);
	numbers.insert(numbers.begin() + 5, 2, 5);
	COUT(BLUE, "numbers");
	vector_status(numbers);

	numbers.push_back(45);
	COUT(BLUE, "numbers");
	vector_status(numbers);

	numbers.pop_back();
	COUT(BLUE, "numbers");
	vector_status(numbers);

	COUT(BLUE, numbers.front());

	COUT(BLUE, numbers.back());

	COUT(BLUE, numbers.at(13));

	// COUT(WHITE, (ft::enable_if<ft::is_integral<ft::vector<int>::iterator>::value>));

	COUT(GREEN, "numbers2");
	ft::vector<int> numbers2(5, 12);
	COUT(GREEN, "numbers2");
	vector_status(numbers2);

	numbers2.swap(numbers);
	COUT(BLUE, "numbers");
	vector_status(numbers);
	COUT(GREEN, "numbers2");
	vector_status(numbers2);
	
	
	numbers2.resize(50);
	vector_status(numbers2);

	numbers2.resize(3);
	vector_status(numbers2);

	numbers2.resize(30, 20);
	vector_status(numbers2);

	numbers2.assign(5, 5);
	vector_status(numbers2);

	numbers2.erase(numbers2.begin() + 3);
	vector_status(numbers2);

	// numbers2.erase(numbers2.begin(), numbers.begin() + 1);
	// vector_status(numbers2);

	// numbers2.insert(numbers2.begin(), numbers.begin(), numbers.end());

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