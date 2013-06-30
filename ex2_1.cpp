/*
 * ex2_1.cpp
 *
 *  Created on: 23/06/2013
 *      Author: bruno
 */

#include <iostream>
#include <boost/type_traits/is_same.hpp>

template<bool b, typename T2, typename T3>
struct if_else {
	typedef T2 value_type;
};

template<typename T2, typename T3>
struct if_else<false, T2, T3> {
	typedef T3 value_type;
};

template<typename FUNC_POINTER, typename T,
		typename T2>
struct replace_func_pointer {
	typedef FUNC_POINTER value_type;
};

template<typename T, typename T2, typename T3>
struct replace_array {
	typedef T value_type;
};

template<typename T, typename T2, typename T3>
struct replace_pointer {
	typedef T value_type;
};

template<typename T, typename T2, typename T3>
struct replace_ref {
	typedef T value_type;
};

template<typename T, typename T2, typename T3>
struct replace_class_member  {
	typedef T value_type;
};

template<typename T, typename T2, typename T3>
struct replace_impl {
	typedef typename replace_func_pointer<
			typename replace_array<
			typename replace_pointer<
			typename replace_ref<
			typename replace_class_member<T, T2, T3>::value_type,
			T2, T3>::value_type,
			T2, T3>::value_type,
			T2, T3>::value_type,
			T2, T3>::value_type value_type;
};

// case T(*func)(T2)
template<typename T, typename T2,
		typename RET, typename PARAM>
struct replace_func_pointer<RET (*)(PARAM), T, T2> {
	typedef typename replace_impl<RET, T, T2>::value_type RET_;
	typedef typename replace_impl<PARAM, T, T2>::value_type PARAM_;
	typedef typename if_else<boost::is_same<RET_, T>::value, T2, RET_>::value_type (*value_type)
			(typename if_else<boost::is_same<PARAM_, T>::value, T2, PARAM_>::value_type);
};

// case T(*func)(T2, T3)
template<typename T, typename T2,
		typename RET, typename PARAM,  typename PARAM2>
struct replace_func_pointer<RET (*)(PARAM, PARAM2), T, T2> {
	typedef typename replace_impl<RET, T, T2>::value_type RET_;
	typedef typename replace_impl<PARAM, T, T2>::value_type PARAM_;
	typedef typename replace_impl<PARAM2, T, T2>::value_type PARAM2_;
	typedef typename if_else<boost::is_same<RET_, T>::value, T2, RET_>::value_type (*value_type)
			(typename if_else<boost::is_same<PARAM_, T>::value, T2, PARAM_>::value_type,
					typename if_else<boost::is_same<PARAM2_, T>::value, T2, PARAM2_>::value_type);
};

template<typename T, typename T2, typename T3, std::size_t N>
struct replace_array<T[N], T2, T3> {
	typedef typename replace_impl<T, T2, T3>::value_type T_;
	typedef typename if_else<boost::is_same<T_, T2>::value, T3, T_>::value_type value_type[N];
};

template<typename T, typename T2, typename T3>
struct replace_pointer<T*, T2, T3> {
	typedef typename replace_impl<T, T2, T3>::value_type T_;
	typedef typename if_else<boost::is_same<T_, T2>::value, T3, T_>::value_type *value_type;
};

template<typename T, typename T2, typename T3>
struct replace_ref<T&, T2, T3> {
	typedef typename replace_impl<T, T2, T3>::value_type T_;
	typedef typename if_else<boost::is_same<T_, T2>::value, T3, T_>::value_type *value_type;
};

template<typename T, typename T2, typename T3, typename T4>
struct replace_class_member<T(T2::*), T3, T4> {
	typedef typename replace_impl<T, T3, T4>::value_type T_;
	typedef typename replace_impl<T2, T3, T4>::value_type T2_;
	typedef typename if_else<boost::is_same<T_, T3>::value, T4, T_>::value_type
			(if_else<boost::is_same<T2_, T3>::value, T4, T2_>::value_type::* value_type);
};

template<typename T, typename T2, typename T3,
		typename RET, typename PARAM>
struct replace_class_member<RET(T::*)(PARAM), T2, T3> {
	typedef typename replace_impl<RET, T2, T3>::value_type RET_;
	typedef typename replace_impl<T, T2, T3>::value_type T_;
	typedef typename replace_impl<PARAM, T2, T3>::value_type PARAM_;
	typedef typename if_else<boost::is_same<RET_, T2>::value, T3, RET_>::value_type
			(if_else<boost::is_same<T_, T2>::value, T3, T_>::value_type::* value_type)
			(typename if_else<boost::is_same<PARAM_, T2>::value, T3, PARAM_>::value_type);
};

template<typename T, typename T2, typename T3,
		typename RET, typename PARAM, typename PARAM2>
struct replace_class_member<RET(T::*)(PARAM, PARAM2), T2, T3> {
	typedef typename replace_impl<RET, T2, T3>::value_type RET_;
	typedef typename replace_impl<T, T2, T3>::value_type T_;
	typedef typename replace_impl<PARAM, T2, T3>::value_type PARAM_;
	typedef typename replace_impl<PARAM2, T2, T3>::value_type PARAM2_;
	typedef typename if_else<boost::is_same<RET_, T2>::value, T3, RET_>::value_type
			(if_else<boost::is_same<T_, T2>::value, T3, T_>::value_type::* value_type)
			(typename if_else<boost::is_same<PARAM_, T2>::value, T3, PARAM_>::value_type,
					typename if_else<boost::is_same<PARAM2_, T2>::value, T3, PARAM2_>::value_type);
};


int bla(int a, int b) {
	return a+b;
}

bool test(char a) {
	return true;
}

char bla2(bool(*func)(char a), char b) {
	if(func(b)) return b;
	return 'a';
}

char bla3(char* a, char b) {
	return 'a';
}

int main(int argc, char *argv[]) {
	bool a = boost::is_same<replace_func_pointer<
			int(*)(bool(*)(int, bool(*)(int)), int), int, char
			>::value_type, char(*)(bool(*)(char, bool(*)(char)), char)
			>::value;

	bool b = boost::is_same<replace_func_pointer<
			void(*)(int), void, int
			>::value_type, int(*)(int)
			>::value;
	bool c = boost::is_same<replace_func_pointer<
			void(*)(char), void, int
			>::value_type, int(*)(char)
			>::value;

	bool d = boost::is_same<replace_func_pointer<
			void(*)(char, char, int), char, bool
			>::value_type, void(*)(bool, bool, int)
			>::value;

	typename replace_func_pointer<
					int(*)(bool(*)(int), int), int, char
					>::value_type myfunc = bla2;


	std::cout <<  "replace_func_pointer\n"
			<< "[ int(*)(bool(*)(int, bool(*)(int)), int), int, char == "
					"char(*)(bool(*)(char, bool(*)(char)), char) ] : "
			<< a << std::endl;
	std::cout <<  "replace_func_pointer\n"
			<< "[ void(*)(int), void, int == is int(*)(int) ] : "
			<< b << std::endl;
	std::cout <<  "replace_func_pointer\n"
			"[ void(*)(char), void, int = int(*)(char) ] : "
			<< c << std::endl;
	std::cout <<  "replace_func_pointer\n"
			"[ void(*)(char, char, int), char, bool = void(*)(char, char, int) ] : "
			<< d << std::endl;

	return 0;
}


