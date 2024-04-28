#include "order.hpp"



std::fstream& operator<<( std::fstream &f,const Order& ord){
    f<<ord.weight<< " " <<ord.district<< " "<<ord.time<<'\n';
    return f;
}
