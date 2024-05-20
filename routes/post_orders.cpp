#ifndef PORDERS_4_5_2024
#define PORDERS_4_5_2024

#include "All_routes.hpp"

// int Order::id=0;
http::status post_orders(std::string json_string, std::string configs)
{
    std::vector<Order> vec;
    nlohmann::json arr;
    try
    {
        arr = nlohmann::json::parse(json_string);
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return http::status::unprocessable_entity;
    }
    try
    {
        connection C(configs);
        work W(C);
        for (auto it = arr.begin(); it != arr.end(); it++)
        {
            int w = (*it)["weight"];
            int d = (*it)["district"];
            std::string t = (*it)["time"];
            vec.push_back(Order(w, d, t));
        }
        for (auto x : vec)
        {
            std::string query = "INSERT INTO \"order\" (weight, district, time) VALUES (your_weight_value, your_district_value, \'your_time_value\');";
            int start = query.find("your_weight_value");
            query.replace(start, 17, std::to_string(x.weight));

            start = query.find("your_district_value");
            query.replace(start, 19, std::to_string(x.district));

            start = query.find("your_time_value");
            query.replace(start, 15, x.time);

            std::cout << query << std::endl;
            W.exec(query);
            std::cout << "you`ve succefully added new note\n";
        }
        W.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return http::status::internal_server_error;
    }

    //  W.conn().disconnect();
    return http::status::ok;
}
#endif
