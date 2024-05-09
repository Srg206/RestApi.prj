#include "All_routes.hpp"

std::vector<Courier> get_couriers(std::string_view url, std::string configs)
{
    connection C(configs);
    work W(C);
    std::vector<Courier> res;
    std::string query = "";

    result got = W.exec("SELECT * FROM public.\"courier\"  ORDER BY id ASC");
    W.commit();
    std::cout << "you`ve succesfully send a query \n"
              << got.size() << std::endl;

    for (auto it = got.begin(); it != got.end(); it++)  
    {
        Courier new_courier;
        new_courier.my_id = it.at("id").as<int>();
        new_courier.district = it.at("district").as<int>();
        new_courier.time = it.at("time").as<std::string>();
        new_courier.type = it.at("type").as<std::string>();
        res.push_back(new_courier);
        std::cout << new_courier << std::endl;
    }

    W.conn().disconnect();

    return res;
}
