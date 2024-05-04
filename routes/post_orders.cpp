#ifndef PORDERS_4_5_2024
#define PORDERS_4_5_2024

#include"All_routes.hpp"
#include<iostream>


int Order::id=0;
int post_orders(std::string json_string){
    nlohmann::json arr = nlohmann::json::parse(json_string);
    std::vector<Order> vec;
    for(auto it=arr.begin();it!=arr.end();it++){
        int w=(*it)["weight"];
        int d=(*it)["district"];
        std::string t=(*it)["time"];
        vec.push_back(Order(w,d,t));
    }
    std::ofstream f("../../resources/orders.txt", std::ios_base::app);
    if(!f.is_open()){
        std::cout<<"Could not open \"order.txt\" !!!";
    }
    for(Order x:vec){
        f<<x.my_id<<" ";
        f<<x;
    }
    f.close();
    return 0;
}
#endif
