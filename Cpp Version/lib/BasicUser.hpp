#include <string>

class BasicUser {
    protected: 
        std::string name; 
        std::string phoneNumber; 
    
    public: 
        BasicUser(std::string name, std::string phoneNumber);
        BasicUser() : name(""), phoneNumber("") {}

        std::string getName();
        void setName(std::string name);
        std::string getPhoneNumber();
        void setPhoneNumber(std::string phone_number); 
};