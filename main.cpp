// #include <server/server.hpp>
#include <iostream>

#include <pqxx/pqxx>
#include <postgresql/libpq-fe.h>
//#include <libpq-fe.h>
using namespace pqxx;
using namespace std;

int main()
{
    std::cout << "Docker is working" << std::endl;
    // Server a("127.0.0.1", 8000);
    // a.Work();
    // connection C("dbname=test-db user=user password=user123 hostaddr=172.16.63.8 port=5432");
    connection C{"postgres://user:user123@172.16.63.8/test-db"}; //"postgresql://user:password@localhost/dbname"
    //C.disconnect();

    return 0;
}