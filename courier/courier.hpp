#ifndef Courier_27_04_2024
#define Courier_27_04_2024

#include<string>
#include<fstream>

struct Courier{
    int district=0; 
    std::string schedule="";
    std::string type="";

};
std::fstream& operator<<( std::fstream &f, const Courier & c);
#endif