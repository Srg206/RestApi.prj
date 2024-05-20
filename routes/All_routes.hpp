#ifndef All_Routes_27_04_2024
#define All_Routes_27_04_2024

#include<courier/courier.hpp>
#include<order/order.hpp>
#include<vector>
#include <nlohmann/json.hpp>
#include<boost/beast.hpp>

#include <fstream>
#include<string_view>
#include <iostream>

#include <pqxx/pqxx> 
using namespace pqxx;

using json = nlohmann::json;
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using net::ip::tcp;
using namespace std::string_literals;

json Order_to_Json(const Order& ord);

json Courier_to_Json(const Courier& c);


http::status post_couriers(std::string json_string, std::string configs);
http::status post_orders(std::string json_string, std::string configs);
http::status post_orders_complete(std::string json_string, std::string configs);


std::pair<http::status,json> get_couriers_id(std::string_view  url, std::string configs);
std::pair<http::status,json> get_couriers(std::string_view  url, std::string configs);

std::pair<http::status,json> get_orders_id(std::string_view  url, std::string configs);
std::pair<http::status,json> get_orders(std::string_view url, std::string configs);



#endif