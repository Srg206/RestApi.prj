#include "All_routes.hpp"

std::pair<http::status, json> get_couriers_id(std::string_view url, std::string configs)
{
    std::cout<<"\nCalled get_couriers_id"<<std::endl;
    json res_json = json();
    try
    {
        std::vector<Courier> res;
        //std::string query = "";
        //std::cout<<"--URL--"<<url;

        std::string tmp(url);
        std::string s = tmp.replace(0, 10, "");
        std::string query = "SELECT * FROM \"courier\" WHERE id = 5;";

        int start = query.find("5");
        query.replace(start, 1, s);
        //std::cout<<s<<"--query--"<<query<<std::endl;
        connection C(configs);
        work W(C);
        result got;

        try
        {

            got = W.exec(query);
            W.commit();

            std::cout << "you`ve succesfully send a query \n"
                      << got.size() << std::endl;

            auto it = got.begin();
            Courier new_courier;
            if (it.at("id").is_null())
            {
                throw std::exception();
            }
            new_courier.my_id = it.at("id").as<int>();
            new_courier.district = it.at("district").as<int>();
            new_courier.time = it.at("time").as<std::string>();
            new_courier.type = it.at("type").as<std::string>();
            res_json = Courier_to_Json(new_courier);
        }
        catch (std::exception &ex)
        {
            std::cout << ex.what();
            return std::make_pair(http::status::not_found, json());
        }
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return std::make_pair(http::status::internal_server_error, json());
    }

    // W.conn().disconnect();
    return std::make_pair(http::status::ok, res_json);
}
