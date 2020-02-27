#include <assert.h>

template <class Target, class Source>
inline Target polymorphic_downcast(Source* x)
{
	assert(dynamic_cast<Target>(x) == x);
	return static_cast<Target>(x);
}
template <class Target, class Source>
inline Target polymorphic_downcast(Source& x)
{
	return static_cast<Target>(x);
}

struct A {
	//neccessary for dynamic_cast
	virtual ~A() {};
};
struct B : A {};

int main()
{
	B b;
	A* a_ptr = &b;
	B* b_ptr = polymorphic_downcast<B*>(a_ptr);
	A& a_ref = b;
	B& b_ref = polymorphic_downcast<B&>(a_ref);
    return 0;
}

