/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:37:25 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/22 10:30:42 by jabenjam         ###   ########.fr       */
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
	COUT_NC("STATUS");
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
	COUT_NC("STATUS");
	COUT_NC("-----------------");
	COUT_NC("size=" << m.size() << std::endl);
	COUT_NC("content:");
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
	ft::map<int, int> m;

	ft::pair<int, int> v = ft::make_pair(0, 1);

	for (size_t i = 0; i < 10 ; i++, v.first++, (v.second *= v.first))
		m.insert(v);
	map_status(m);

	ft::map<int, int> m2(m.begin(), (--(--(--(--m.end())))));
	map_status(m2);

	ft::map<int, int> m3(m2);
	map_status(m3);

	COUT_NC("OPERATOR=");

	m3 = m;
	map_status(m3);
	m2 = m3;
	map_status(m);

	COUT_NC(std::endl << "ITERATOR --- BEGIN");
	COUT_NC("m.begin()->first = " << m.begin()->first\
		<< std::endl << "(++(++(m.begin())))->first = " << (++(++(m.begin())))->first);

	COUT_NC(std::endl << "ITERATOR --- END");
	COUT_NC(std::endl << "(--m.end())->first = " << (--m.end())->first\
		<< std::endl << "(--(--(m.end())))->first = " << (--(--(m.end())))->first);

	COUT_NC(std::endl << "ITERATOR --- BEGIN --- CONST");
	ft::map<int, int>::const_iterator cit = m.begin();
	COUT_NC(std::endl << "m.const_iterator(begin) key = " << cit->first << std::endl);

	COUT_NC("REVERSE_ITERATOR");

	COUT_NC(std::endl << "REVERSE_ITERATOR --- RBEGIN");
	COUT_NC("m.rbegin()->first = " << m.rbegin()->first\
		<< std::endl << "(++(++(m.rbegin())))->first = " << (++(++(m.rbegin())))->first);

	COUT_NC(std::endl << "REVERSE_ITERATOR --- REND");
	COUT_NC(std::endl << "(--m.rend())->first = " << (--m.rend())->first\
		<< std::endl << "(--(--(m.rend())))->first = " << (--(--(m.rend())))->first);

	COUT_NC(std::endl << "CAPACITY");

	ft::map<std::string, std::string> m4;

	COUT_NC("EMPTY = " << m4.empty() << std::endl << "SIZE = " << m4.size());


	COUT_NC(std::endl << "MAX SIZE");
	COUT_NC(std::endl << "MAX SIZE = " << m4.max_size() << std::endl);

	m4.insert(ft::make_pair("A", "A"));
	m4.insert(ft::make_pair("BB", "BB"));
	m4.insert(ft::make_pair("CCC", "CCC"));

	COUT_NC(std::endl << "EMPTY");
	COUT_NC(std::endl << "EMPTY = " << m4.empty() << std::endl << "SIZE = " << m4.size());
	COUT_NC(std::endl << "MAX SIZE = " << m4.max_size() << std::endl);

	COUT_NC(std::endl << "ELEMENT ACCESS");

	COUT_NC(std::endl << "m4[\"BB\"] = " << m4["BB"] << std::endl);
	COUT_NC(std::endl << "m[4] = " << m[4] << std::endl);

	COUT_NC(std::endl << "MODIFIERS");
	COUT_NC(std::endl << "INSERT");
	COUT_NC(std::endl << "BEFORE INSERT");
	map_status(m);
	ft::pair<ft::map<int, int>::iterator, bool> ret = m.insert(ft::make_pair(13, 42));

	COUT_NC(std::endl << "RETURN = " << ret.first->first << " " << ret.first->second);
	COUT_NC(std::endl << "AFTER INSERT");
	map_status(m);

	COUT_NC(std::endl << "NEW INSERT");
	ft::map<int, int>::iterator it = m.insert(++(++(++(m.begin()))), ft::make_pair(10, 42));
	COUT_NC(std::endl << "RETURN = " << it->first << " " << it->second);
	COUT_NC(std::endl << "AFTER INSERT");
	map_status(m);
	
	COUT_NC(std::endl << "BEFORE INSERT");
	map_status(m2);
	m2.insert(--(--(--m.end())), m.end());
	COUT_NC(std::endl << "AFTER INSERT");
	map_status(m2);

	COUT_NC(std::endl << "ERASE");

	COUT_NC(std::endl << "BEFORE ERASE");
	map_status(m2);
	m2.erase(m2.begin());
	COUT_NC(std::endl << "AFTER ERASE");
	map_status(m2);

	COUT_NC(std::endl << "ERASE KEY = 9");
	m2.erase(9);
	COUT_NC(std::endl << "AFTER ERASE");
	map_status(m2);

	COUT_NC(std::endl << "ERASE FROM BEGIN + 3 TO END");
	m2.erase(++(++(++m2.begin())), m2.end());
	COUT_NC(std::endl << "AFTER ERASE");
	map_status(m2);

	COUT_NC(std::endl << "SWAP");
	COUT_NC(std::endl << "MAP 1 =");
	map_status(m3);
	COUT_NC(std::endl << "MAP 2 =");
	map_status(m2);
	COUT_NC(std::endl << "AFTER SWAPPING MAP 1 WITH MAP 2");
	m3.swap(m2);
	map_status(m3);

	COUT_NC(std::endl << "CLEAR");

	COUT_NC(std::endl << "BEFORE CLEAR");
	map_status(m2);
	m2.clear();
	COUT_NC(std::endl << "AFTER CLEAR");
	map_status(m2);

	COUT_NC(std::endl << "FIND");

	COUT_NC(std::endl << "MAP =");
	map_status(m);

	COUT_NC(std::endl << "TRYING TO FIND 0");
	it = m.find(0);
	COUT_NC(std::endl << "SEARCH RESULT " << it->first << " " << it->second);
	COUT_NC(std::endl << "TRYING TO FIND 9");
	it = m.find(9);
	COUT_NC(std::endl << "SEARCH_RESULT " << it->first << " " << it->second);

	COUT_NC(std::endl << "COUNT");

	COUT_NC(std::endl << "COUNTING KEY = 0");
	size_t ret1 = m.count(0);
	COUT_NC(std::endl << "RESULT " << ret1);
	COUT_NC(std::endl << "COUNTING KEY = 11");
	ret1 = m.count(11);
	COUT_NC(std::endl << "RESULT " << ret1);

	COUT_NC(std::endl << "LOWER BOUND");

	COUT_NC(std::endl << "MAP =");
	map_status(m);

	COUT_NC(std::endl << "LOWER BOUND --- 5");
	it = m.lower_bound(5);
	COUT_NC(std::endl << "RESULT " << it->first << " " << it->second);
	COUT_NC(std::endl << "LOWER BOUND --- 13");
	it = m.lower_bound(13);
	COUT_NC(std::endl << "RESULT " << it->first << " " << it->second);

	COUT_NC(std::endl << "UPPER BOUND");

	COUT_NC(std::endl << "UPPER BOUND --- 5");
	it = m.upper_bound(5);
	COUT_NC(std::endl << "RESULT " << it->first << " " << it->second);
	COUT_NC(std::endl << "UPPER BOUND --- 10");
	it = m.upper_bound(10);
	COUT_NC(std::endl << "RESULT " << it->first << " " << it->second);
}

int main()
{
	vector_tests();
	stack_tests();
	map_tests();
	return (0);
}
