#ifndef Server_21_04_2024
#define Server_21_04_2024

//#include<boost/beast.hpp>
#include<boost/asio.hpp>
#include<string>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <routes/All_routes.hpp>
#include<string_view>
#include <pqxx/pqxx> 
#include <regex>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace pqxx;
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using net::ip::tcp;
using namespace std::string_literals;



std::string ReplaceAll(const std::string& inputStr, const std::string& src, const std::string& dst);
std::string get_configs();

class Server{
private:
    boost::asio::ip::tcp::endpoint endpnt = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8000);
    void handleConnection(boost::asio::ip::tcp::socket& socket);
    void handleRequest(boost::asio::ip::tcp::socket& socket, const http::request<http::string_body>& req);
    bool Init();

public:
    Server();
    Server(std::string ip_adr, int port);
    Server(const Server& another_serv)=delete;
    Server(Server && another_serv)=delete;
    ~Server()=default;

    Server& operator=(const Server& another_serv)=delete;
    Server& operator=(Server&& another_serv)=delete;

    void Work();
};

#endif