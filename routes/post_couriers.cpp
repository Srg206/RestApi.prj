#include"All_routes.hpp"

//int Courier::id=0;

int post_couriers(std::string json_string){
    connection C{"postgres://user:user123@10.54.65.132:5432/test-db"}; //"postgresql://user:password@localhost/dbname"
    work W(C);
    nlohmann::json arr = nlohmann::json::parse(json_string);
    std::vector<Courier> vec;
    for (auto it = arr.begin(); it != arr.end(); it++)
    {
        int d = (*it)["district"];
        std::string t = (*it)["time"];
        std::string type=(*it)["type"];
        vec.push_back(Courier(d, t, type));
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
            std::string query = "INSERT INTO \"courier\" (district, time, type) VALUES (your_district_value, \'your_time_value\' , \'your_type_value\');";
            int start = query.find("your_type_value");
            query.replace(start, 15, x.type);

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


    return 200;
}

