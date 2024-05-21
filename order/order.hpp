#ifndef Order_27_04_2024
#define Order_27_04_2024

#include<string>
#include<fstream>

struct Order{
    static int id;
    int my_id;
    int weight=0;
    int district=0; 
    std::string time="";
    bool IsReady=false;
    Order()=default;
    Order(int w, int d, std::string t);
    Order(int id,int w, int d, std::string t);
    Order(int id,int w, int d, std::string t,bool ir);

};

std::ofstream& operator<<( std::ofstream &f,const Order& ord );
std::ifstream& operator>>( std::ifstream &f,Order& ord );


std::ostream& operator<<( std::ostream &o,const Order& ord );
std::istream& operator>>( std::istream &i,Order& ord );


#endif