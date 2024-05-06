#include"All_routes.hpp"
#include<iostream>
Order get_orders_id(std::string_view  url){
    //std::cout<<"\n\n"<<url.data()<<"\n\n";
    std::string s(url.data()+8);
    //std::cout<<s;
    int gotten_id=std::stoi(s);
    std::ifstream f("../../resources/orders.txt");
    Order tmp;
    while(!f.eof()){
        f>>tmp;
        if(tmp.my_id==gotten_id){
            return tmp;
        }
    }
    f.close();
    //throw std::invalid_argument("There are no Order with such id\n");

    return Order();
}