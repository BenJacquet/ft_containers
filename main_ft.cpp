/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:37:25 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/16 17:18:30 by jabenjam         ###   ########.fr       */
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

# define _END			"\x1b[0m"
# define _BOLD			"\x1b[1m"
# define _UNDER			"\x1b[4m"
# define _REV			"\x1b[7m"

/*
** Colors
*/
# define _GREY			"\x1b[30m"
# define _RED			"\x1b[31m"
# define _GREEN			"\x1b[32m"
# define _YELLOW		"\x1b[33m"
# define _BLUE			"\x1b[34m"
# define _PURPLE		"\x1b[35m"
# define _CYAN			"\x1b[36m"
# define _WHITE			"\x1b[37m"

/*
** Inverted, i.e. colored backgrounds
*/
# define _IGREY			"\x1b[40m"
# define _IRED			"\x1b[41m"
# define _IGREEN		"\x1b[42m"
# define _IYELLOW		"\x1b[43m"
# define _IBLUE			"\x1b[44m"
# define _IPURPLE		"\x1b[45m"
# define _ICYAN			"\x1b[46m"
# define _IWHITE		"\x1b[47m"

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

void test_reverse_iterator()
{
	COUT_NC("TEST1");
	ft::vector<int> vct;
	COUT_NC("TEST2");
	ft::vector<int>::iterator it = vct.begin();
	COUT_NC("TEST3");
	ft::vector<int>::const_iterator cit = vct.begin();
	COUT_NC("TEST4");
	ft::vector<int>::reverse_iterator rit(it);
	COUT_NC("TEST5");
	ft::vector<int>::const_reverse_iterator crit(rit);
	COUT_NC("TEST6");
	ft::vector<int>::const_reverse_iterator crit_(it);
	COUT_NC("TEST7");
	ft::vector<int>::const_reverse_iterator crit_2(cit);
	COUT_NC("TEST8");
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

	test_reverse_iterator();
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

template <class Key, class T>
void	print(ft::map<Key, T>& lst)
{
	std::cout << "printing a map : \n";
	for (typename ft::map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';
}

int		erase_test()
{
	  ft::map<char,int> mymap;
  ft::map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

  it=mymap.find('b');
  std::cout << "found b\n";
  mymap.erase (it);                   // erasing by iterator
  std::cout << "erase iterator to b\n";
  mymap.erase ('c');                  // erasing by key
  std::cout << "erase by key 'c'\n";
  it=mymap.find ('e');
//   mymap.display();
  std::cout << "erase by range 'e' to end\n";
  mymap.erase ( it, mymap.end() );    // erasing by range
//   mymap.display();

  std::cout << " display :\n";
  // show content:
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

int		test_lmartin()
{
	std::cout << _WHITE << "# test_map" << _END << std::endl;
	std::cout << _YELLOW <<  "/* ********************************************************************** */" << std::endl;
	std::cout << "/*                          "<< _WHITE << "BASIC TESTS" << _YELLOW << "                                   */" << std::endl;
	std::cout << "/* ********************************************************************** */" << _END << std::endl;
	std::cout << std::endl;


	ft::map<std::string, int> mymap;
	print(mymap);


	std::cout << "mymap<" << _PURPLE << "string" << _END << ", " << _PURPLE << "int" << _END <<"> mymap;" << std::endl;

	std::cout << std::endl;
	std::cout << "mymap.max_size(): " << (mymap.max_size() > 10000) << std::endl;
	print(mymap);
	std::cout << std::endl;


	print(mymap);
	mymap.insert(ft::pair<std::string, int>("ft", 42));

	print(mymap);
	mymap.insert(ft::pair<std::string, int>("one", 1));


	std::cout << _WHITE << "# testing upper/lower_bound" << _END << std::endl;
	ft::map<std::string, int>::iterator mit;
	ft::map<std::string, int>::iterator it;
	print(mymap);
	it = mymap.lower_bound("aaa");
	print(mymap);
	std::cout << std::setw(40) << "mymap.lower_bound(\"aaa\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	print(mymap);
	it = mymap.lower_bound("one");
	print(mymap);
	std::cout << std::setw(40) << "mymap.lower_bound(\"one\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	print(mymap);
	it = mymap.lower_bound("oae");
	print(mymap);
	std::cout << std::setw(40) << "mymap.lower_bound(\"oae\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	print(mymap);
	it = mymap.lower_bound("ft");
	print(mymap);
	std::cout << std::setw(40) << "mymap.lower_bound(\"ft\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	print(mymap);
	it = mymap.lower_bound("zzz");
	print(mymap);
	
	if (it == mymap.end())
		std::cout << std::setw(40) << "mymap.lower_bound(\"zzz\"): mymap.end()" << std::endl;
	std::cout << std::endl;
	print(mymap);
	it = mymap.upper_bound("aaa");
	
	print(mymap);
	std::cout << std::setw(40) << "mymap.upper_bound(\"aaa\"): " << it->first << ":" << it->second << std::endl;;
	std::cout << std::endl;
	print(mymap);
	it = mymap.upper_bound("oae");
	print(mymap);
	std::cout << std::setw(40) << "mymap.upper_bound(\"oae\"): " << it->first << ":" << it->second << std::endl;;
	std::cout << std::endl;
	print(mymap);
	it = mymap.upper_bound("one");
	
	if (it == mymap.end())
		std::cout << std::setw(40) << "mymap.upper_bound(\"one\"): mymap.end()" << std::endl;
	print(mymap);
	std::cout << std::endl;
	it = mymap.upper_bound("ft");
	print(mymap);
	std::cout << std::setw(40) << "mymap.upper_bound(\"ft\"): " << it->first << ":" << it->second << std::endl;;
	std::cout << std::endl;
	print(mymap);
	it = mymap.upper_bound("zzz");
	
	if (it == mymap.end())
		std::cout << std::setw(40) << "mymap.upper_bound(\"zzz\"): mymap.end()" << std::endl;
	print(mymap);
	std::cout << std::endl;

	print(mymap);
	mymap.erase("undefined");
	print(mymap);
	mymap.erase("ft");
	print(mymap);
	std::cout << _WHITE << "# double clear" << _END << std::endl;
	mymap.clear();
	print(mymap);
	mymap.clear();
	print(mymap);
	mymap["lol"];
	print(mymap);
	mymap.insert(ft::pair<std::string, int>("xD", 123));
	print(mymap);
	mymap.insert(mymap.end(), ft::pair<std::string, int>("uch", 442));
	print(mymap);
	mymap.insert(mymap.begin(), ft::pair<std::string, int>("uch", 22));
	print(mymap);
	mymap.insert(mymap.end(), ft::pair<std::string, int>("uch", 23));
	print(mymap);
	mymap.insert(ft::pair<std::string, int>("uch", 23));
	print(mymap);
	mymap["lol"] = 8;


	print(mymap);
	ft::map<std::string, int> map2;

	print(mymap);
	print(map2);
	std::cout << "mymap<" << _PURPLE << "string" << _END << ", " << _PURPLE << "int" << _END <<"> mymap2;" << std::endl;
	print(mymap);
	std::cout << "empty line\n";
	print(map2);
	std::cout << "empty line2\n";

	swap(mymap, map2);
	std::cout << "empty line3\n";
	print(mymap);
	std::cout << "empty line4\n";
	print(map2);
	std::cout << "empty line5\n";

	mymap = map2;
	print(mymap);
	print(map2);

	std::cout << std::setw(40) << "map == map2: " << (mymap == map2) << std::endl;
	print(mymap);
	print(map2);
	std::cout << std::endl;

	mymap.clear();
	print(mymap);
	print(map2);

	mymap["satan"] = 666;
	print(mymap);
	print(map2);
	std::cout << std::setw(40) << "mymap == map2: " << (mymap == map2) << std::endl;
	print(mymap);
	print(map2);
	std::cout << std::endl;
	std::cout << std::setw(40) << "mymap <= map2: " << (mymap <= map2) << std::endl;
	print(mymap);
	print(map2);
	std::cout << std::endl;
	std::cout << std::setw(40) << "mymap >= map2: " << (mymap >= map2) << std::endl;
	print(mymap);
	print(map2);
	std::cout << std::endl;
	std::cout << std::setw(40) << "mymap > map2: " << (mymap > map2) << std::endl;
	print(mymap);
	print(map2);
	std::cout << std::endl;
	std::cout << std::setw(40) << "mymap < map2: " << (mymap > map2) << std::endl;
	print(mymap);
	print(map2);
	std::cout << std::endl;

	return 0;
}

void	map_tests()
{
	COUT_NC("---------------------- MAP ----------------------");
	ft::map<std::string, int>	testmap;

	COUT_NC("Empty :\nsize = " << testmap.size());
	testmap.insert(ft::make_pair("test", 15));
	COUT_NC("After single insert :\nsize = " << testmap.size());
	COUT_NC("fin");
	test_lmartin();
	erase_test();
}

int main()
{
	vector_tests();
	stack_tests();
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