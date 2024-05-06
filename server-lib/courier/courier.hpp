#ifndef Courier_27_04_2024
#define Courier_27_04_2024

#include<string>
#include<fstream>

struct Courier{
    static int id;
    int my_id;
    int district=0; 
    std::string schedule="";
    std::string type="";
    Courier()=default;
    Courier(int d, std::string s, std::string t);

};
std::ofstream& operator<<( std::ofstream &f, const Courier & c);
std::ifstream& operator>>( std::ifstream &f,Courier & c);

std::ostream& operator<<( std::ostream &o, const Courier & c);
std::istream& operator>>( std::istream &i,Courier & c);


#endif