#include "All_routes.hpp"

int post_orders_complete(std::string json_string)
{
    nlohmann::json arr = nlohmann::json::parse(json_string);
    std::vector<int> ids = arr.get<std::vector<int>>();
    connection C{"postgres://user:user123@172.16.63.8:5432/test-db"}; //"postgresql://user:password@localhost/dbname"

    work W(C);
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
        // std::string query = "UPDATE \"order\" SET isready=true WHERE id = 1;";
        // W.exec(query);

        for (int x : ids)
        {
            std::cout << x << std::endl;
            std::string query = "UPDATE \"order\" SET isready=true WHERE id = current_id;";
            int start = query.find("current_id");
            query.replace(start, 10, std::to_string(x));
            std::cout<<query;
            W.exec(query);
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