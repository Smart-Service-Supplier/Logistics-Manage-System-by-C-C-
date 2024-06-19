#include "Address.hpp"

Address::Address(std::string province, std::string city, std::string ward, std::string street_name, std::string address_in_detail) {
    this->province = province;
    this->city = city;
    this->ward = ward; 
    this->street_name = street_name;
    this->address_in_detail = address_in_detail;
}
