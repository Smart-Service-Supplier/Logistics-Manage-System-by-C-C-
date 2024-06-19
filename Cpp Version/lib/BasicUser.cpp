#include "BasicUser.hpp"

BasicUser::BasicUser(std::string name, std::string phoneNumber) {
    this->name = name;
    this->phoneNumber = phoneNumber;
}

std::string BasicUser::getName(){
    return this->name; 
}

void BasicUser::setName(std::string name) {
    this->name = name;
}

std::string BasicUser::getPhoneNumber() {
    return this->phoneNumber;
}

void BasicUser::setPhoneNumber(std::string phone_number) {
    this->phoneNumber = phone_number;
}