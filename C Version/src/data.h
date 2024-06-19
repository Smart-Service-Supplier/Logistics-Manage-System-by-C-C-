#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define STRING_SIZE 100
#define MAX_DEALS 10

typedef struct 
{
    char province[STRING_SIZE]; 
    char city[STRING_SIZE];
    char ward[STRING_SIZE];
    char street_name[STRING_SIZE];
    char address_number [STRING_SIZE];
}address;

typedef enum 
{
    at_sender,
    in_transfer,
    at_warehouse,
    shipping,
    at_receiver
}deal_status;


typedef struct deal deal;

typedef struct 
{
    char name[STRING_SIZE];
    char phone_number[STRING_SIZE];
    address address_user;
    int number_of_deal;
    deal ** deal_list;
}user;

struct deal
{
    user sender;
    user receiver;
    char item_name[STRING_SIZE];
    float item_weight;
    char deal_code[11];
    deal_status status;
};

void enter_user_infor(user* Usser_input);
void user_assign(user* user_dest, user user_source);
void display_user(user user);
void display_deal(deal deal);
void generateCode(char* code);
void create_deal(deal* deal, user *sender, user *receiver);
void find_Deal(const user* currentUser, const char* dealCode);
void print_all_user_deals(const user* currentUser);
void free_memory(user* currentUser);
