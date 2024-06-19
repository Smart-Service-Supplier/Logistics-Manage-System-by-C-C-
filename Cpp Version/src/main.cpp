#include <iostream>
#include "screen.hpp"

int main(int argc, char **argv) {
    Screen *scr = new Screen(LOGIN); 

    while (true) {
        Intro *e = new Intro;  
        e->loading(); 
        e->display_1();
        e->loading();
        scr->clear();
        delete e; 
        break; 
    }
    User* admin = new User;
    Deal* deal = new Deal; 

    while (true) {
        if (scr->id == LOGIN) {
            scr->display_login(admin); 
            scr->clear();
        }
        else if (scr->id == CRE_USER) {
            scr->display_create_user(admin);
            scr->clear();
        }
        else if (scr->id == HOME) {
            scr->display_home();
            // send->sender->setName(admin->getName());
            // send->sender->setPhoneNumber(admin->getPhoneNumber());

          
            deal->sender->setName(admin->getName());
            deal->sender->setPhoneNumber(admin->getPhoneNumber());

            scr->clear();
        }
        else if (scr->id == CUSTOMER) {
            scr->display_customer_input(deal);
            scr->clear();
        }
        else if (scr->id == ITEM) {
            scr->display_item_input(deal);
            scr->clear();
        }
        else if (scr->id == MANAGE_DEAL) {
            scr->display_manage_deal();
            scr->clear();
        }
        else if (scr->id == RECV_LIST) {
            scr->display_recv_deal_list(admin);
            scr->clear();
        }
        else if (scr->id == SEND_LIST) {
            scr->display_send_deal_list(admin);
            scr->clear();
        }
        else if (scr->id == DEAL_ACTION) {
            scr->display_deal_action(admin);
            scr->clear();
        } 
        else if (scr->id == EDIT_INFOR) {
            scr->display_edit_infor(admin);
            scr->clear();
        } 
    }
    return 0; 
    std::string a;
}