#ifndef All_Routes_27_04_2024
#define All_Routes_27_04_2024

#include<courier/courier.hpp>
#include<order/order.hpp>
#include<vector>
#include <nlohmann/json.hpp>

#include <fstream>
#include<string_view>
#include <iostream>

#include <pqxx/pqxx> 
using namespace pqxx;


int post_couriers(std::string json_string, std::string configs);
int post_orders(std::string json_string, std::string configs);
int post_orders_complete(std::string json_string, std::string configs);


Courier get_couriers_id(std::string_view  url, std::string configs);
std::vector<Courier> get_couriers(std::string_view  url, std::string configs);

Order get_orders_id(std::string_view  url, std::string configs);
std::vector<Order> get_orders(std::string_view url, std::string configs);



#endif