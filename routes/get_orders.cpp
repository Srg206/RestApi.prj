#include "All_routes.hpp"

std::pair<http::status, json> get_orders(std::string_view url, std::string configs)
{
    json res_str = json::array();

    try
    {

        std::vector<Order> res;
        std::string query = "";

        connection C(configs);
        work W(C);
        result got;

        try
        {
            got = W.exec("SELECT * FROM public.\"order\"  ORDER BY id ASC");
            W.commit();

            std::cout << "you`ve succesfully send a query \n"
                      << got.size() << std::endl;
        }
        catch (std::exception &ex)
        {
            std::cout << ex.what() << std::endl;
            return std::make_pair(http::status::not_found, json());
        }

        for (auto it = got.begin(); it != got.end(); it++)
        {
            Order new_ord;
            new_ord.my_id = it.at("id").as<int>();
            new_ord.weight = it.at("weight").as<int>();
            new_ord.district = it.at("district").as<int>();
            new_ord.time = it.at("time").as<std::string>();
            new_ord.IsReady = it.at("isready").as<bool>();
            res_str.push_back(Order_to_Json(new_ord));
        }
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return std::make_pair(http::status::internal_server_error, json());
    }

    return std::make_pair(http::status::ok, res_str);
}
