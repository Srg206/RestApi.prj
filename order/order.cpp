#include "order.hpp"

int Order::id=0;


std::ofstream& operator<<( std::ofstream &f,const Order& ord){
    f<<ord.weight<< " " <<ord.district<< " "<<ord.time<<'\n';
    return f;
}

std::ifstream &operator>>(std::ifstream &f,Order &ord){
    f>>ord.my_id>>ord.weight>>ord.district>>ord.time;
    return f;
}

std::ostream &operator<<(std::ostream &o, const Order &ord)
{
    o<<ord.my_id<<" "<<ord.weight<<" "<<ord.district<<" "<<ord.time;
    return o;
}

std::istream &operator>>(std::istream &i, Order &ord)
{
    i>>ord.my_id>>ord.weight>>ord.district>>ord.time;

    return i;
}

Order::Order(int w, int d, std::string t):
weight(w),district(d),time(t)
{
}

Order::Order(int id, int w, int d, std::string t) : my_id(id), weight(w), district(d), time(t)
{
    my_id=id++;
}

Order::Order(int id, int w, int d, std::string t, bool ir):
my_id(id), weight(w), district(d), time(t), IsReady(ir)
{
}
