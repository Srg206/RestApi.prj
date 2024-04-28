#include <server/server.hpp>
//#include <boost/asio.hpp>


#include<fstream>

int main()
{
    //Server a("127.0.0.1", 8000);
    //a.Work();
    std::ofstream f("fake_db");
    std::cout<<f.is_open()<<"nnnnnnnn";
    f<<"mmvmvmmvd";

    // Дальнейший код
    return 0;
}