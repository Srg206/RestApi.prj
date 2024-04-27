#include "server.hpp"

std::map<std::string, std::string> jsonToMap(const std::string &jsonString)
{
    std::map<std::string, std::string> result;
    try
    {
        auto j = nlohmann::json::parse(jsonString);
        for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it)
        {
            if (it.value().is_string())
            {
                result[it.key()] = it.value();
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
    return result;
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
    std::cout << "hndlreq   " << req.method_string() << "   \n";
    if (req.method() == boost::beast::http::verb::get)
    {
        std::cout << "send\n\n\n";
        std::string h = "200\r\n"; // The status code is already finished with a '\r\n'
        std::string t = "Date: hhhhh \r\n";
        // std::string s = "Server: Muffin 1.0\r\n";

        std::string const content = "<html><body><h1>Hello World</h1><p>This is a web server in c++</p></body></html><html><body><h1>Hello World</h1><p>This is a web server in c++</p></body></html>";
        std::string type = "Content-Type: text/html\r\n";
        std::string length = "Content-Length: " + std::to_string(content.size()) + "\r\n";
        std::string res = h + t + length + type + "\r\n" + content + "\r\n";

        http::response<http::string_body> respn{http::status::ok, 11};
        respn.set(http::field::server, "Boost Beast Server");
        respn.set(http::field::content_type, "text/html");
        respn.body() = content;
        respn.prepare_payload();

        http::write(socket, respn);

        // http::write(socket, boost::asio::buffer("HTTP/1.1 200 OK\nContent-Type: text/html\n"));
    }
    if (req.method() == boost::beast::http::verb::post)
    {
        net::write(socket, boost::asio::buffer("\n POST 200 \n"));
    }
}
void Server::handleConnection(boost::asio::ip::tcp::socket &socket)
{
    boost::asio::streambuf buffer;
    http::request<http::string_body> req;

    net::streambuf buf;
    http::read(socket, buf, req);

    std::cout << "Method: " << req.method() << "\n";
    handleRequest(socket, req);
    // std::cout << "URL: " << req.target() << "\n";
    // for(auto it=req.begin(); it!=req.end(); it++){
    //     std::cout<<(*it).value() <<std::endl;
    // }
    // auto it=req.begin();
    // std::cout<<(*it).value() <<std::endl;

    std::cout << "end of handle" << std::endl;
}

void Server::Work()
{

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, endpnt);
    while (true)
    {
        boost::asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        /*std::string greating = "You`v succesfully connected to the server!\n";
       boost::asio::write(socket, boost::asio::buffer(greating)); */

        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "Got connection from: " << socket.remote_endpoint() << std::endl;

        std::thread newconnection([this, &socket]()
                                  { this->handleConnection(socket); });
        // std::thread newconnection(handleConnection, std::ref(socket));

        newconnection.join();
    }
}
