#include "All_routes.hpp"
Order get_orders_id(std::string_view url, std::string configs)
{
    connection C(configs);
    work W(C);
    // std::cout<<"\n\n"<<url.data()<<"\n\n";
    std::string tmp(url);
    std::string s=tmp.replace(0,8,"");
    std::cout<<"this is s"<<s<<std::endl;
    int gotten_id = std::stoi(s);
    std::string query = "SELECT * FROM \"order\" WHERE id = 5;";

    int start = query.find("5");
    query.replace(start, 1, s);
    std::cout << s << std::endl;
    std::cout << query << std::endl;

    result got = W.exec(query);
    W.commit();
    std::cout << "you`ve succesfully send a query \n"
              << got.size() << std::endl;
    Order new_ord;
    auto it = got.begin();
    new_ord.my_id = it.at("id").as<int>();
    new_ord.weight = it.at("weight").as<int>();
    new_ord.district = it.at("district").as<int>();
    new_ord.time = it.at("time").as<std::string>();
    new_ord.IsReady = it.at("isready").as<bool>();
    W.conn().disconnect();
    return new_ord;
}