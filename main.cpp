#include <server/server.hpp>
#include <iostream>

//#include <pqxx/pqxx> 
 
using namespace std;
 
int main(int argc, char* argv[])
{
   Server a("127.0.0.1", 8000);
   a.Work();
   //std::cout<<"start\n\n\n\n\ndfbmfkbmfkbmkfmbkfmbkmfkbmfkbm\n\n\n\ndmned an app";
   // try{
   //    connection C{"postgres://user:user123@10.54.65.132:5432/test-db"}; //"postgresql://user:password@localhost/dbname"
   //    if (C.is_open()) {
   //       cout << "Opened database successfully: " << C.dbname() << endl;
   //    } else {
   //       cout << "Can't open database" << endl;
   //       return 1;
   //    }
   //    C.disconnect ();
   // }catch (const std::exception &e){
   //    cerr << e.what() << std::endl;
   //    return 1;
   // }
   return 0;
}
    
    
    
    