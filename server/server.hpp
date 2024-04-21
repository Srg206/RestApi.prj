#ifndef Server_21_04_2024
#define Server_21_04_2024

#include<boost/beast.hpp>
#include<boost/asio.hpp>
#include<string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>
#include <list>


class Server{
private:
    boost::asio::io_context io_context;
  //boost::asio::ip::tcp::endpoint endpnt(boost::asio::ip::address::from_string("127.0.0.1"), 8080); //???????
    boost::asio::ip::tcp::endpoint endpnt=boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080);
    std::list<boost::asio::ip::tcp::socket> sockets;
   
   
    void handleConnection(boost::asio::ip::tcp::socket& socket);
public:
    Server()=default;
    Server(std::string ip_adr, int port);
    Server(std::filesystem::path path_to_configs);
    Server(const Server& another_serv);
    Server(Server && another_serv);
    ~Server();

    Server& operator=(const Server& another_serv);
    Server& operator=(Server&& another_serv);

    bool Init(std::filesystem::path path_to_configs);
    void Work();





};

#endif