#ifndef UTILS_21_05_2024
#define UTILS_21_05_2024

#include "All_routes.hpp"

json Order_to_Json(const Order& ord){
    json jsonObject;
    jsonObject["id"] = ord.my_id;
    jsonObject["weight"] = ord.weight;
    jsonObject["district"] = ord.district;
    jsonObject["time"] = ord.time;
    jsonObject["isready"] = ord.IsReady;
    return jsonObject;
}

json Courier_to_Json(const Courier& c){
    json jsonObject;
    jsonObject["id"] = c.my_id;
    jsonObject["district"] = c.district;
    jsonObject["time"] = c.time;
    jsonObject["type"] = c.type;
    return jsonObject;

}
#endif