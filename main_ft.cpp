/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:37:25 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/21 22:17:34 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// TESTS PERSO

#include "utils/utils.hpp"
#include "containers/vector.hpp"
#include "containers/stack.hpp"
#include "containers/map.hpp"
#include <vector>
#include <stack>
#include <map>
#include <cstdio>
#include <iomanip>

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

template<typename T, typename T2>
void map_status(ft::map<T, T2> &m)
{
	typename ft::map<T, T2>::iterator it = m.begin();
	typename ft::map<T, T2>::iterator ite = m.end();

	COUT_NC("-----------------");
	COUT_NC("size=" << m.size() << std::endl);
	for (;it != ite; it++)
		COUT_NC("key=" << it->first << " val=" << it->second);
	COUT_NC("-----------------" << std::endl);
}

void	vector_tests()
{
	COUT_NC("-------------------------------------------- VECTOR --------------------------------------------");
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
	COUT_NC(std::endl);

	COUT_NC("BACK");
	COUT_NC(numbers.back());
	COUT_NC(std::endl);

	COUT_NC("AT");
	COUT_NC(numbers.at(13));
	COUT_NC(std::endl);

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

}

void	stack_tests()
{
	COUT_NC("-------------------------------------------- STACK --------------------------------------------");
	ft::stack<int> numbers;


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
	ft::map<std::string, int>	testmap;

}

int main()
{
	vector_tests();
	stack_tests();
	map_tests();
	return (0);
}
