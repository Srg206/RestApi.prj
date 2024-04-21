#include "server.hpp"

Server::Server(std::string ip_adr, int port)
{
    endpnt.address(boost::asio::ip::address::from_string(ip_adr));
    endpnt.port(port);
}

Server::Server(std::filesystem::path path_to_configs)
{
    std::ifstream file(path_to_configs.filename());
    std::string ip;
    int port_num;
    file >> ip >> port_num;
    endpnt.address(boost::asio::ip::address::from_string(ip));
    endpnt.port(port_num);
}

Server::Server(const Server &another_serv)
{
}

Server::Server(Server &&another_serv):
endpnt(std::move(another_serv.endpnt)),sockets(std::move(another_serv.sockets))
{}

Server::~Server()
{
    for (auto it = sockets.begin(); it != sockets.end(); it++)
    {
        (*it).close();
    }
}

Server &Server::operator=(const Server &another_serv)
{
   return *this;
}

Server &Server::operator=(Server &&another_serv)
{
    endpnt=std::move(another_serv.endpnt);
    sockets=std::move(another_serv.sockets);
    return *this;
}

bool Server::Init(std::filesystem::path path_to_configs)
{
    try{
        std::ifstream file(path_to_configs.filename());
        std::string ip;
        int port_num;
        file >> ip >> port_num;
        endpnt.address(boost::asio::ip::address::from_string(ip));
        endpnt.port(port_num);
    }
    catch(...){
        std::cout<<"Something went wrong!!! Could not init server"<<std::endl;
        return 1;
    }
    return 0;
}

void Server::handleConnection(boost::asio::ip::tcp::socket &socket){

}
void Server::Work(){
    boost::asio::ip::tcp::acceptor acceptor( io_context,endpnt);
    while (true)
    {
        boost::asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        /*   std::string greating = "You`v succesfully connected to the server!\n";
           boost::asio::write(socket, boost::asio::buffer(greating)); */

        std::thread newconnection([this, &socket]() { this->handleConnection(socket); });
        newconnection.join();
    }
}
