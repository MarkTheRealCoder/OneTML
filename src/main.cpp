#include <type_traits>
#include <iostream>
#include <nlohmann/json.hpp>
#include "environment/ObjectTML.h"


int main() {

    onetml::DynamicType t;
    t = (long double)5.103334555L;
    long double a = t;

    float c = t;
    std::cout << c << std::endl;
    std::cout << a << std::endl;
    return 0;
}





