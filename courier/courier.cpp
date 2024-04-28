#include "courier.hpp"

std::fstream& operator<<(std::fstream &f, const Courier & c){
    f<<c.district<<" "<<c.schedule<<" "<<c.type<<"\n";
    return f;
}
