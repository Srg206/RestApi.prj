#ifndef All_Routes_27_04_2024
#define All_Routes_27_04_2024

#include<courier/courier.hpp>
#include<order/order.hpp>
#include<vector>
#include <nlohmann/json.hpp>
#include <fstream>




int post_couriers(nlohmann::json arr);
int post_orders(std::string arr);
int post_orders_complete(nlohmann::json arr);


Courier get_couriers_id(std::string_view  url);
std::vector<Courier> get_couriers(std::string_view  url);

Order get_orders_id(std::string_view  url);
std::vector<Order> get_orders(std::string_view url);



#endif