#include"All_routes.hpp"
#include<iostream>

std::vector<Order> get_orders(std::string_view url){
    std::ifstream f("../../resources/orders.txt");
    std::vector<Order> res;
    Order tmp;
    while(!f.eof()){
        f>>tmp;
        res.push_back(tmp);
    }
    f.close();

    return res;

}
