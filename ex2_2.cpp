/*
 * ex2_2.cpp
 *
 *  Created on: 30/06/2013
 *      Author: bruno
 */

#include <cassert>

#include <boost/type_traits/is_base_and_derived.hpp>

template <class Target, class Source>
inline Target polymorphic_downcast(Source* x)
{
	if(boost::is_base_and_derived<Target, Source>::value)
		return static_cast<Target>(x);
}

template <class Target, class Source>
inline Target polymorphic_downcast(Source& x)
{
	if(boost::is_base_and_derived<Target, Source>::value)
		return static_cast<Target>(x);
}

int main(int argc, char **argv) {

	return 0;
}

