#include <string>
#include <iostream>

class Address {
    public: 
        std::string province;
        std::string city;
        std::string ward;
        std::string street_name;
        std::string address_in_detail; 

        Address(std::string province, std::string city, std::string ward, std::string street_name, std::string address_in_detail);
        Address() : province(""), city(""), ward(""), street_name(""), address_in_detail("") {}
};