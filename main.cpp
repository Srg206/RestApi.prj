#include <server/server.hpp>
#include <iostream>
// #include <pqxx/pqxx>

using namespace std;

int main(int argc, char *argv[])
{

    setlocale(LC_ALL, "Russian");

    //char buffer[1024];
    //GetModuleFileName(NULL, buffer, sizeof(buffer));
    //std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    //std::cout << std::string(buffer).substr(0, pos); 
   Server a;
   a.Work();
   return 0;
}
