#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <server/server.hpp>
#include <cstdlib>
#include <boost/asio.hpp>

TEST_CASE("Routes/utils")
{
    Order ord(3, 45, 3, "12:40", false);
    json json_obj = Order_to_Json(ord);
    CHECK_EQ(json_obj.at("id"), ord.my_id);
    CHECK_EQ(json_obj.at("weight"), ord.weight);
    CHECK_EQ(json_obj.at("district"), ord.district);
    CHECK_EQ(json_obj.at("time"), ord.time);
    CHECK_EQ(json_obj.at("isready"), ord.IsReady);

    Courier c(4, 5, "12:88", "driver");
    json_obj = Courier_to_Json(c);
    CHECK_EQ(json_obj.at("id"), c.my_id);
    CHECK_EQ(json_obj.at("district"), c.district);
    CHECK_EQ(json_obj.at("time"), c.time);
    CHECK_EQ(json_obj.at("type"), c.type);
}
TEST_CASE("API")
{
    system("python3 ../../../tests/api_tests.py");
}

