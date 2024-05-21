#include <server/server.hpp>
#include <iostream>

// #include <pqxx/pqxx>

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << argv[1] << "\n";

   auto path = std::filesystem::current_path(); // getting path
   std::filesystem::current_path(path);
   path = std::filesystem::current_path();
   std::cout<<path.filename()<<std::endl;


   Server a;
   a.Work();
   return 0;
}
