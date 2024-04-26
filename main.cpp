#include <server/server.hpp>
#include <boost/asio.hpp>




int main()
{
    Server a("127.0.0.1", 8000);
    a.Work();
    // Дальнейший код
    return 0;
}