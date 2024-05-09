#include "server.hpp"

std::string ReplaceAll(const std::string &inputStr, const std::string &src, const std::string &dst)
{
    std::regex rx(src.c_str());
    return std::regex_replace(inputStr, rx, dst);
}

std::string get_configs()
{
    std::ifstream f("../../env.txt");
    std::string configs;
    f >> configs;
    std::cout << configs;
    return configs;
}

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
    std::cout << "handleRequest" <<std::endl;
    std::string_view url(req.target().data(), req.target().size());
    std::string real_url(url);
    std::cout << url.data() << std::endl;

    if (req.method() == boost::beast::http::verb::get)
    {
        std::cout << "uRl-------"<<url << std::endl;
        if (url.find("couriers/") != -1)
        {
            //get_couriers_id(url, get_configs());
            std::cout << url.data() << std::endl;
        }
        else if (url.find("orders/") != -1)
        {
            std::cout << url.data() << std::endl;
            std::cout << get_orders_id(url, get_configs()) << std::endl;
        }
        else if (url.find("couriers") != -1)
        {
            get_couriers(url, get_configs());
            std::cout << "get_couriers" << std::endl;
        }
        else if (url.find("orders") != -1)
        {
            std::cout << "get_orders" << std::endl;
            std::vector<Order> all_orders = get_orders(url, get_configs());
            // std::cout << *all_orders.begin() << all_orders[10]<< std::endl;
        }
    }
    if (req.method() == boost::beast::http::verb::post)
    {
        std::cout << "uRl---"<< url << std::endl;
        // nlohmann::json second = nlohmann::json::parse(req.body());
        if (url.find("couriers") != -1)
        {
            post_couriers(req.body(), get_configs());
            std::cout << "post_couriers" << std::endl;
        }
        else if (url.find("orders/complete") != -1)
        {
            std::cout << "post_orders/complete" << std::endl;
            post_orders_complete(req.body(), get_configs());
        }
        else if (url.find("orders") != -1)
        {
            post_orders(req.body(), get_configs());
            std::cout << "post_orders" << std::endl;
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
    //std::mutex mtx;
    //mtx.lock();
    std::cout<<"handle new connection\n"<<std::this_thread::get_id();
    //mtx.lock();

    // boost::asio::streambuf buffer;
    //std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    //mtx.lock();
    http::request<http::string_body> req;
    net::streambuf buf;
    http::read(socket, buf, req);
    handleRequest(socket, req);
    //http::read(socket, buf, req);
    //req.clear();
    //buf.consume(buf.size());
    //std::cout<<"END OF HANDING\n"<<std::this_thread::get_id();
   // mtx.unlock();

}

void Server::Work()
{

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, endpnt);
    int chunk_of_connections = 12;
    int now_connected = 0;
    while (true)
    {
        boost::asio::ip::tcp::socket socket(io_context);
        //std::cout<<"new socket created\n"<<std::this_thread::get_id();
        acceptor.accept(socket);

        /*std::string greating = "You`v succesfully connected to the server!\n";
       boost::asio::write(socket, boost::asio::buffer(greating)); */
        std::cout << "Got connection from: " << socket.remote_endpoint() << std::endl;

        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        now_connected++;
        // if()
        std::thread newconnection([this, &socket]()
                                  { this->handleConnection(socket); });
        // std::thread newconnection(handleConnection, std::ref(socket));

        newconnection.join();
    }
}
