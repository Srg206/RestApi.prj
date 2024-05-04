#include <server/server.hpp>

int main()
{
    Server a("127.0.0.1", 8000);
    a.Work();

    return 0;
}