#ifndef PORDERS_4_5_2024
#define PORDERS_4_5_2024

#include "All_routes.hpp"
#include <iostream>

// int Order::id=0;
int post_orders(std::string json_string)
{
    connection C{"postgres://user:user123@172.16.63.8:5432/test-db"}; //"postgresql://user:password@localhost/dbname"
    work W(C);
    nlohmann::json arr = nlohmann::json::parse(json_string);
    std::vector<Order> vec;
    for (auto it = arr.begin(); it != arr.end(); it++)
    {
        int w = (*it)["weight"];
        int d = (*it)["district"];
        std::string t = (*it)["time"];
        vec.push_back(Order(w, d, t));
    }
    std::cout << "Working post orders" << std::endl;
    try
    {
        if (C.is_open())
        {
            std::cout << "Opened database successfully: " << C.dbname() << std::endl;
        }
        else
        {
            std::cout << "Can't open database" << std::endl;
            return 1;
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
            try
            {
                W.exec(query);
                std::cout << "you`ve succefully added new note\n";
            }
            catch (const std::exception &exc)
            {
                std::cerr << exc.what() << std::endl;
                return 1;
            }
        }
        W.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    C.disconnect();
    return 0;
}
#endif
