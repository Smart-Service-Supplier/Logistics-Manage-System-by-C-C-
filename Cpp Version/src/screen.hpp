#include "../lib/Objects.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include "../lib/Intro.hpp"
#include <stdlib.h>

enum screen_type {
    LOGIN = 1, 
    CRE_USER,
    HOME,
    CUSTOMER,
    ITEM, 
    MANAGE_DEAL, 
    RECV_LIST, 
    SEND_LIST, 
    DEAL_ACTION,
    EDIT_INFOR, 
    CLEAR, 
    Handler
};

class Screen {
    public: 
        screen_type id;
        
        Screen(screen_type id);

        void display_login(User* user); 
        void display_create_user(User* user);
        void display_home(); // main screen

        // Create a new deal
        void display_customer_input(Deal *deal);
        void display_item_input(Deal *deal); 

        // Deal Manager
        void display_manage_deal();
        void display_recv_deal_list(User *admin);
        void display_send_deal_list(User *admin);
        void display_deal_action(User* admin); 

        // Edit User Information
        void display_edit_infor(User *admin); 
    
        void clear();
        void display_handle_message(screen_type id); 

};