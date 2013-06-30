#include <iostream>
#include <string>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/has_equal_to.hpp>


template<typename T, typename T2 = T>
class Base {
public:
    static typename boost::has_equal_to<T, T2>::value_type
        impl(T a, T2 b) {
            return (a == b);
    }

};

int main(int argc, char **argv) {

    if(Base<std::string, std::string>::impl("aa", "aa")) 
    {
        std::cout << "true\n";
    } else {
        std::cout << "false\n";
    }

    return 0;
}
