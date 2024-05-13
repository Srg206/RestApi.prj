#include "All_routes.hpp"

std::vector<Order> get_orders(std::string_view url, std::string configs)
{
    connection C(configs);
    work W(C);
    std::vector<Order> res;
    std::string query = "";

    result got = W.exec("SELECT * FROM public.\"order\"  ORDER BY id ASC");
    W.commit();
    std::cout << "you`ve succesfully send a query \n"
              << got.size() << std::endl;

    for (auto it = got.begin(); it != got.end(); it++)
    {
        Order new_ord;
        new_ord.my_id = it.at("id").as<int>();
        new_ord.weight = it.at("weight").as<int>();
        new_ord.district = it.at("district").as<int>();
        new_ord.time = it.at("time").as<std::string>();
        new_ord.IsReady = it.at("isready").as<bool>();
        res.push_back(new_ord);
        std::cout << new_ord << std::endl;
    }
    return res;
}
