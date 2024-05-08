#include "All_routes.hpp"

Courier get_couriers_id(std::string_view url)
{
    std::cout<<"\n\n"<<url.data()<<"\n\n"; 
    std::string s(url.data() +10);
    std::cout<<s;
    int gotten_id = std::stoi(s);

    connection C{"postgres://user:user123@172.16.63.8:5432/test-db"}; //"postgresql://user:password@localhost/dbname"
    work W(C);
    std::string query = "SELECT * FROM \"courier\" WHERE id = 5;";

    int start = query.find("5");
    query.replace(start, 1, s);
    std::cout << s << std::endl;
    std::cout << query << std::endl;

    result got = W.exec(query);
    W.commit();
    std::cout << "you`ve succesfully send a query \n"
              << got.size() << std::endl;
    Courier new_courier;
    auto it = got.begin();
    new_courier.my_id = it.at("id").as<int>();
    new_courier.district = it.at("district").as<int>();
    new_courier.time = it.at("time").as<std::string>();
    new_courier.type = it.at("type").as<std::string>();

    std::cout<<new_courier<<std::endl;
    C.disconnect();
    return new_courier;
}
