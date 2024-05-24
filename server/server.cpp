#include "server.hpp"

std::string ReplaceAll(const std::string &inputStr, const std::string &src, const std::string &dst)
{
    std::regex rx(src.c_str());
    return std::regex_replace(inputStr, rx, dst);
}

std::string get_configs()
{
#if defined(_WIN32) || defined(_WIN64)
    std::string path_to_configs = ("../../../env.txt");
#else
    std::string path_to_configs = ("../../env.txt");
#endif
    std::ifstream file(path_to_configs);
    std::string configs;
    file >> configs;
    std::cout << configs;
    return configs;
}
Server::Server()
{
    try
    {
#if defined(_WIN32) || defined(_WIN64)
        std::string path_to_configs = ("../../../env.txt");
#else
        std::string path_to_configs = ("../../env.txt");
#endif
        //std::string path_to_configs = ("../env.txt");
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::cout << "Current Path: " << currentPath << std::endl;
        std::ifstream file(path_to_configs);
        std::string ip;
        int port_num;
        std::string url_todb;
        file >> url_todb >> ip >> port_num;
        std::cout << ip << port_num << std::endl;
        // endpnt.address(boost::asio::ip::address::from_string(ip));
        // endpnt.port(port_num);
        endpnt = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port_num);
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << '\n';
    }
}
Server::Server(std::string ip_adr, int port)
{
    endpnt.address(boost::asio::ip::address::from_string(ip_adr));
    endpnt.port(port);
}

void Server::handleRequest(boost::asio::ip::tcp::socket &socket, const http::request<http::string_body> &req)
{
    std::cout << "handleRequest" << std::endl;
    std::string_view url(req.target().data(), req.target().size());
    std::string real_url(url);
    std::cout << url.data() << std::endl;

    std::pair<http::status, json> content_status;
    http::status status_code;
    if (req.method() == boost::beast::http::verb::get)
    {
        std::cout << "uRl-------" << url << std::endl;
        if (url.find("couriers/") != -1)
        {
            content_status = get_couriers_id(url, get_configs());
            std::cout << "1" << std::endl;
        }
        else if (url.find("orders/") != -1)
        {
            content_status = get_orders_id(url, get_configs());
        }
        else if (url.find("couriers") != -1)
        {
            content_status = get_couriers(url, get_configs());
        }
        else if (url.find("orders") != -1)
        {
            content_status = get_orders(url, get_configs());
        }
        http::response<http::string_body> respn{content_status.first, 11};
        respn.set(http::field::server, "Boost Beast Server");
        respn.set(http::field::content_type, "text/html");
        respn.body() = content_status.second.dump(); // content;
        std::cout << content_status.second.dump()<< "  "<< content_status.first << std::endl;
        respn.prepare_payload();
        http::write(socket, respn);
    }
    if (req.method() == boost::beast::http::verb::post)
    {
        std::cout << "uRl---" << url << std::endl;
        // nlohmann::json second = nlohmann::json::parse(req.body());
        if (url.find("couriers") != -1)
        {
            status_code = post_couriers(req.body(), get_configs());
        }
        else if (url.find("orders/complete") != -1)
        {
            status_code = post_orders_complete(req.body(), get_configs());
        }
        else if (url.find("orders") != -1)
        {
            status_code = post_orders(req.body(), get_configs());
        }
        http::response<http::string_body> respn{status_code, 11};
        respn.set(http::field::server, "Boost Beast Server");
        respn.set(http::field::content_type, "text/html");
        respn.body() = ""; // content;
        respn.prepare_payload();
        http::write(socket, respn);
    }
    std::cout << "End of handling request" << std::endl;
}
void Server::handleConnection(boost::asio::ip::tcp::socket &socket)
{
    // std::mutex mtx;
    // mtx.lock();
    std::cout << "handle new connection\n"
              << std::this_thread::get_id();
    // mtx.lock();

    // boost::asio::streambuf buffer;
    // std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    // mtx.lock();
    http::request<http::string_body> req;
    net::streambuf buf;
    http::read(socket, buf, req);
    handleRequest(socket, req);
    // http::read(socket, buf, req);
    // req.clear();
    // buf.consume(buf.size());
    // std::cout<<"END OF HANDING\n"<<std::this_thread::get_id();
    // mtx.unlock();
}

void Server::Work()
{

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, endpnt);
    while (true)
    {
        boost::asio::ip::tcp::socket socket(io_context);
        // std::cout<<"new socket created\n"<<std::this_thread::get_id();
        acceptor.accept(socket);

        /*std::string greating = "You`v succesfully connected to the server!\n";
       boost::asio::write(socket, boost::asio::buffer(greating)); */
        std::cout << "Got connection from: " << socket.remote_endpoint() << std::endl;

        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        // if()
        std::thread newconnection([this, &socket]()
                                  { this->handleConnection(socket); });
        // std::thread newconnection(handleConnection, std::ref(socket));

        newconnection.join();
    }
}
