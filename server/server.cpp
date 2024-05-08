#include "server.hpp"

// std::map<std::string, std::string> jsonToMap(const std::string &jsonString)
// {
//     std::map<std::string, std::string> result;
//     try
//     {
//         auto j = nlohmann::json::parse(jsonString);
//         for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it)
//         {
//             if (it.value().is_string())
//             {
//                 result[it.key()] = it.value();
//             }
//         }
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "Error parsing JSON: " << e.what() << std::endl;
//     }
//     return result;
// }

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

bool Server::Init(std::filesystem::path path_to_configs)
{
    try
    {
        std::ifstream file(path_to_configs.filename());
        std::string ip;
        int port_num;
        file >> ip >> port_num;
        endpnt.address(boost::asio::ip::address::from_string(ip));
        endpnt.port(port_num);
    }
    catch (...)
    {
        std::cout << "Something went wrong!!! Could not init server" << std::endl;
        return 1;
    }
    return 0;
}

void Server::handleRequest(boost::asio::ip::tcp::socket &socket, const http::request<http::string_body> &req)
{
    std::string_view url(req.target().data(), req.target().size());
    if (req.method() == boost::beast::http::verb::get)
    {
        nlohmann::json second = nlohmann::json::parse(req.body());
        //std::cout << url << std::endl;
        if (url.find("couriers/")!=-1){      
            get_couriers_id(url);
            std::cout << "get_couriers/" << std::endl;
        }
        else if (url.find("orders/")!=-1){
            
            std::cout << get_orders_id(url) << std::endl;
        }
        else if (url.find("couriers")!=-1){
            get_couriers(url);
            std::cout << "get_couriers" << std::endl;
        }
        else if (url.find("orders")!=-1){
            std::vector<Order> all_orders=get_orders(url);
            //std::cout << *all_orders.begin() << all_orders[10]<< std::endl;
        }

    }
    if (req.method() == boost::beast::http::verb::post)
    {
        //std::cout << url << std::endl;
        if (url.find("couriers")!=-1){
            post_couriers(req.body());
            std::cout<<"post_couriers"<<std::endl;
        }
        else if (url.find("orders/complete")!=-1){
            std::cout<<"post_orders/complete"<<std::endl;
            post_orders_complete(req.body());
        }
        else if (url.find("orders")!=-1){
            post_orders(req.body());
            std::cout<<"post_orders"<<std::endl;
        }

    }

        std::string content = std::to_string(socket.remote_endpoint().port());
        http::response<http::string_body> respn{http::status::ok, 11};
        respn.set(http::field::server, "Boost Beast Server");
        respn.set(http::field::content_type, "text/html");
        respn.body() = content;
        respn.prepare_payload();
        http::write(socket, respn);
}
void Server::handleConnection(boost::asio::ip::tcp::socket &socket)
{
    boost::asio::streambuf buffer;
    http::request<http::string_body> req;
    net::streambuf buf;
    http::read(socket, buf, req);
    handleRequest(socket, req);
    req.clear();
}

void Server::Work()
{

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, endpnt);
    int chunk_of_connections=12;
    int now_connected=0;
    while (true)
    {
        boost::asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        /*std::string greating = "You`v succesfully connected to the server!\n";
       boost::asio::write(socket, boost::asio::buffer(greating)); */

        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "Got connection from: " << socket.remote_endpoint() << std::endl;
        now_connected++;
        //if()
        std::thread newconnection([this, &socket]()
                                  { this->handleConnection(socket); });
        // std::thread newconnection(handleConnection, std::ref(socket));

        newconnection.join();
    }
}
