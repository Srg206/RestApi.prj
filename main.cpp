#include <server/server.hpp>
//#include <boost/asio.hpp>


//#include<fstream>
//#include<iostream>
//#include<string>



int main()
{
    //Server a("127.0.0.1", 8000);
    //a.Work();
    std::ofstream f("resources/fake_db.txt");
    f<<"mвалmmиььи\n\n\n\n\nn\nvmmvd\n"<<std::endl;
    f.close();
    std::ifstream f2("resources/fake_db.txt");
    std::string str;
    f2>>str;

    std::cout<<str;
    f2.close();
    return 0;
}