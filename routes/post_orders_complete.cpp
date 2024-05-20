#include "All_routes.hpp"

http::status post_orders_complete(std::string json_string, std::string configs)
{
    std::vector<int> ids;
    try
    {
        nlohmann::json arr = nlohmann::json::parse(json_string);
        ids = arr.get<std::vector<int>>();
    }
    catch(std::exception& ex){
        std::cout<<ex.what()<<std::endl;
        return http::status::unprocessable_entity;
    }
    try
    {
        connection C(configs);
        work W(C);
        for (int x : ids)
        {
            std::cout << x << std::endl;
            std::string query = "UPDATE \"order\" SET isready=true WHERE id = current_id;";
            int start = query.find("current_id");
            query.replace(start, 10, std::to_string(x));
            std::cout << query;
            W.exec(query);
        }
        W.commit();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return http::status::internal_server_error;
    }

    // W.conn().disconnect();
    return http::status::ok;
}