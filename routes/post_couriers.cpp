#include "All_routes.hpp"

// int Courier::id=0;

http::status post_couriers(std::string json_string, std::string configs)
{
    nlohmann::json arr;
    std::vector<Courier> vec;
    try
    {
        arr = nlohmann::json::parse(json_string);
        for (auto it = arr.begin(); it != arr.end(); it++)
        {
            int d = (*it)["district"];
            std::string t = (*it)["time"];
            std::string type = (*it)["type"];
            vec.push_back(Courier(d, t, type));
        }
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

        for (auto x : vec)
        {
            std::string query = "INSERT INTO \"courier\" (district, time, type) VALUES (your_district_value, \'your_time_value\' , \'your_type_value\');";
            int start = query.find("your_type_value");
            query.replace(start, 15, x.type);

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
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return http::status::internal_server_error;
    }
    return http::status::ok;
}
