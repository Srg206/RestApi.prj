#include "All_routes.hpp"

int post_orders_complete(std::string json_string, std::string configs)
{
    connection C(configs);
    work W(C);
    nlohmann::json arr = nlohmann::json::parse(json_string);
    std::vector<int> ids = arr.get<std::vector<int>>();
    try
    {
        if (W.conn().is_open())
        {
            std::cout << "Opened database successfully: " << W.conn().dbname() << std::endl;
        }
        else
        {
            std::cout << "Can't open database" << std::endl;
            return 1;
        }
        // std::string query = "UPDATE \"order\" SET isready=true WHERE id = 1;";
        // W.exec(query);

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
        std::cerr << e.what() << std::endl;
        return 1;
    }

    W.conn().disconnect();
    return 0;
}