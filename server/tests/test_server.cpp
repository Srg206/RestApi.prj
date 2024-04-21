#include"../server.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"



TEST_CASE("ctors"){
    Server a;
    Server b;
    Server c(a);
    Server d(std::move(a));
    d=std::move(b);


    

}