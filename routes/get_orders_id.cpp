#include "All_routes.hpp"
Order get_orders_id(std::string_view url)
{
    // std::cout<<"\n\n"<<url.data()<<"\n\n";
    std::string s(url.data() + 8);
    // std::cout<<s;
    int gotten_id = std::stoi(s);

    connection C{"postgres://user:user123@10.54.65.132:5432/test-db"}; //"postgresql://user:password@localhost/dbname"
    work W(C);
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
    C.disconnect();
    return new_ord;
}