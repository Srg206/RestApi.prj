#include <server/server.hpp>
#include <iostream>


#include <iostream>
#include <pqxx/pqxx> 
 
using namespace std;
using namespace pqxx;
 
int main(int argc, char* argv[])
{
   try{
      connection C{"postgres://user:user123@10.54.65.132:5432/test-db"}; //"postgresql://user:password@localhost/dbname"
      //connection C("dbname=testdb user=postgres password=123456 hostaddr=10.4.36.43 port=5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }
      C.disconnect ();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }
}