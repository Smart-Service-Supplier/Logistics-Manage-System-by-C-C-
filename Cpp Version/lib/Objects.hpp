#include "BasicUser.hpp"
#include "Address.hpp"
#include <vector>
#include "config.h"
#include <fstream>
#include "Tool.hpp"

class Item {
    private: 
        std::string name; 
        double weight; 
        bool fragile; 

    public: 
        Item() : name(""), weight(0), fragile(false) {}
        Item(std::string name, double weight); 

        void setName(std::string name);
        void setWeight(double weight);
        void setIsFragile(bool isFragile);

        bool isFragile(); 
        std::string getName();
        double getWeight();

        void display();
};

enum DealStatus {
    PROCESSING = 0, 
    ACCEPTED,
    TOOK_ITEMS,  
    IN_STOCK,
    DELIVERING, 
    ARRIVED, 
    FINISHED
};

const std::string STATUS[7] = {"PROCESSING", "ACCEPTED", "ITEMS TAKEN", "IN_STOCK", "DELIVERING", "ARRIVED", "FINISHED"};

class Deal {
    private: 
        std::string code; 
    
    public:   
        bool type; 
        BasicUser *sender = new BasicUser;
        BasicUser *receiver = new BasicUser; 
        Address *address = new Address;
        std::vector<Item> list;
        DealStatus status;
        int fee; 

        void setCode(std::string code);
        std::string getCode();

        void Self_update();
        void Self_delete();
        void Self_update_status();

        void display();

};

class User : public BasicUser {
    private: 
        std::string password; 
        std::string account; 
    
    public:  
        Address address;

        std::string getAccount();
        std::string getPassword();
        void setAccount(std::string account);
        void setPassword(std::string password);
};
