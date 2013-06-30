/*
 * ex2_0.cpp
 *
 *  Created on: 23/06/2013
 *      Author: bruno
 */

#include <iostream>
#include <boost/type_traits/is_same.hpp>

template<typename T>
struct add_const_ref {
	typedef T const& type;
};

template<typename T>
struct add_const_ref<T &> {
	typedef T type;
};

int main(int argc, char *argv[]) {
	bool is_ref = boost::is_same<add_const_ref<int &>::type, int>::value;
	std::cout << "is_ref (int &): " << is_ref << std::endl;
	is_ref = boost::is_same<add_const_ref<int>::type, int>::value;
	std::cout << "is_ref (int): " << is_ref << std::endl;
	is_ref = boost::is_same<add_const_ref<int const &>::type, int const>::value;
	std::cout << "is_ref (int const &): " << is_ref << std::endl;

	return 0;
}

