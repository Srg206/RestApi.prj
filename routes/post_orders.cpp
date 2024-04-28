#include"All_routes.hpp"
#include<iostream>




int post_orders(std::string json_string){
    nlohmann::json arr = nlohmann::json::parse(json_string);
    std::vector<Order> vec;
    for(auto it=arr.begin();it!=arr.end();it++){
        int w=(*it)["weight"];
        int d=(*it)["district"];
        //std::string t=(*it)["time"];
        vec.push_back(Order{w,d,""});
        //vec.push_back(Order{(*it)["weight"],(*it)["district"],(*it)["time"]});
    }

    std::ofstream f("fake_db.txt");
    f<<"nns[mlw,]";
    if(!f.is_open()){
        std::cout<<"mmmmmm";
    }
    std::cout<<vec.size()<<std::endl;
    for(Order x:vec){
        //f<<x;
        //  f<<"jvnjfnvjnfjvnfjvnfjvnfjnv";
        //x>>f;

    }
    f.close();
    return 0;
}
