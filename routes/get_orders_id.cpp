#include "All_routes.hpp"
std::pair<http::status, json> get_orders_id(std::string_view url, std::string configs)
{
    json res_str;
    try
    {
        std::string tmp(url);
        std::string s = tmp.replace(0, 8, "");
        int gotten_id = std::stoi(s);
        std::string query = "SELECT * FROM \"order\" WHERE id = 5;";

        int start = query.find("5");
        query.replace(start, 1, s);

        connection C(configs);
        work W(C);
        result got;
        try
        {
            got = W.exec(query);
            W.commit();

            // std::cout << "you`ve succesfully send a query \n"
            //           << got.size() << std::endl;
            Order new_ord;
            auto it = got.begin();

            if(it.at("id").is_null()){
                throw std::exception();
            }
            new_ord.my_id = it.at("id").as<int>();
            new_ord.weight = it.at("weight").as<int>();
            new_ord.district = it.at("district").as<int>();
            new_ord.time = it.at("time").as<std::string>();
            new_ord.IsReady = it.at("isready").as<bool>();
      
            res_str = Order_to_Json(new_ord);
        }
        catch (std::exception &ex)
        {
            std::cout << ex.what() << std::endl;
            return std::make_pair(http::status::not_found, json());
        }
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return std::make_pair(http::status::internal_server_error, json());
    }
    catch(...){
        return std::make_pair(http::status::internal_server_error, json());
    }
    return std::make_pair(http::status::ok, res_str);
}