#include "courier.hpp"

std::ofstream& operator<<(std::ofstream &f, const Courier & c){
    f<<c.my_id<< " "<<c.district<<" "<<c.schedule<<" "<<c.type<<"\n";
    return f;
}

std::ifstream &operator>>(std::ifstream &f,Courier &c){

    f>>c.my_id>>c.district>>c.schedule>>c.type;
}

std::ostream &operator<<(std::ostream &o, const Courier &c)
{
    o<<c.my_id<<" "<<c.district<<" "<<c.schedule<< " "<<c.type<<"\n";
    return o;
    // TODO: insert return statement here
}

std::istream &operator>>(std::istream &i, Courier &c)
{
    return i;
    // TODO: insert return statement here
}

Courier::Courier(int d, std::string s, std::string t):
district(d),schedule(s),type(t)
{
    my_id=id++;

}
