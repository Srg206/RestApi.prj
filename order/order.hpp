#ifndef Order_27_04_2024
#define Order_27_04_2024

#include<string>
#include<fstream>

struct Order{
    int weight=0;
    int district=0; 
    std::string time="";
};
std::fstream& operator<<( std::fstream &f,const Order& ord );
#endif