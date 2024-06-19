#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define STRING_SIZE 100

void generateCode(char* code) {
    srand(time(NULL)); // Khởi tạo seed cho hàm ngẫu nhiên

    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int charsetSize = sizeof(charset) - 1; // Kích thước của bộ ký tự

    for (int i = 0; i < 10; i++) {
        int randomIndex = rand() % charsetSize; // Chọn một chỉ số ngẫu nhiên từ 0 đến kích thước của bộ ký tự - 1
        code[i] = charset[randomIndex]; // Lấy ký tự tại chỉ số ngẫu nhiên và gán vào chuỗi code
    }

    code[10] = '\0'; // Kết thúc chuỗi bằng ký tự null
}



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
const char* deal_status_strings[] =
{
    "at_sender",
    "in_transfer",
    "at_warehouse",
    "shipping",
    "at_receiver"
};

void printDealStatus(deal_status status) {
    if (status >= at_sender && status <= at_receiver) {
        printf("Deal Status: %s\n", deal_status_strings[status]);
    } else {
        printf("Invalid Deal Status\n");
    }
}
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
void addDeal(user* currentUser);
void printDeals(const user* currentUser);
void freeMemory(user* currentUser);
void enter_user_infor(user* Usser_input);
void user_assign(user* user_dest, user user_source);
void assign(user* user_dest, user user_source);
void findDeal(const user* currentUser, const char* dealCode);
void display_user(user user)
{
    printf("Name: %s\n", user.name);
    printf("Phone Number: %s\n", user.phone_number);
    printf("Province: %s\n", user.address_user.province);
    printf("City: %s\n", user.address_user.city);
    printf("Ward: %s\n", user.address_user.ward);
    printf("Street name: %s\n", user.address_user.street_name);
    printf("Address number: %s\n", user.address_user.address_number);
    printf("Number of available deal: %d \n", user.number_of_deal);
}
void create_deal(deal* deal, user *sender, user *receiver)
{
    deal->sender = *sender;
    deal->receiver = *receiver;
    printf("Enter Item Name: ");
    gets(deal->item_name);
    fflush(stdin);
    printf("Enter Item Weight: ");
    scanf("%f", &deal->item_weight);
    generateCode(deal->deal_code);
    deal->status = at_sender;
    sender->number_of_deal++;
    sender->deal_list[sender->number_of_deal -1] = deal;
    receiver->number_of_deal++;
    receiver->deal_list[receiver->number_of_deal -1] = deal;
}
/**************************************************************************************************************************** */
int main()
{
    user user_1;
    // strcpy(user.province, "Ba Ria Vung Tau");
    enter_user_infor(&user_1);
    assign(&user_1, user_1);
    user user_2;
    enter_user_infor(&user_2);
    assign(&user_2, user_2);
    deal deal_test;
    create_deal(&deal_test, &user_1, &user_2);
    // deal_test.sender = user_1;
    // deal_test.receiver = user_2;
    // strcpy(deal_test.item_name, "laptop");
    // deal_test.item_weight = 10.0f;
    // generateCode(deal_test.deal_code);
    // deal_test.status = at_sender;
    // display_user(user_1);
    display_user(deal_test.sender);
    display_user(deal_test.receiver);
    printf("Item name: %s\n", deal_test.item_name);
    printf("Item weight: %f\n", deal_test.item_weight);     
    printf("Deal code: %s\n", deal_test.deal_code);
    printDealStatus(deal_test.status);
    printf("Cai nay o trong sender: %s",user_1.deal_list[0]->item_name);
    printf("Cai nay cung o trong sender: %d",user_1.number_of_deal);
    return 0;
}

void enter_user_infor(user* User_input)
{
    printf("Enter name: ");
    gets(User_input -> name);
    fflush(stdin);
    printf("Enter phone number: ");
    gets(User_input -> phone_number);
    fflush(stdin);
    printf("Enter Province: ");
    gets(User_input -> address_user.province);
    fflush(stdin);
    printf("Enter City: ");
    gets(User_input -> address_user.city);
    fflush(stdin);
    printf("Enter Ward: ");
    gets(User_input -> address_user.ward);
    fflush(stdin);
    printf("Enter Street name: ");
    gets(User_input -> address_user.street_name);
    fflush(stdin);
    printf("Enter Address number: ");
    gets(User_input -> address_user.address_number);
    fflush(stdin);
}
void assign(user* user_dest, user user_source)
{
    strcpy(user_dest->name, user_source.name);
    strcpy(user_dest->phone_number, user_source.phone_number);
    strcpy(user_dest->address_user.province, user_source.address_user.province);
    strcpy(user_dest->address_user.city, user_source.address_user.city);
    strcpy(user_dest->address_user.ward, user_source.address_user.ward);
    strcpy(user_dest->address_user.street_name, user_source.address_user.street_name);
    strcpy(user_dest->address_user.address_number, user_source.address_user.address_number);
    user_dest -> number_of_deal = 0;
    user_dest ->deal_list = (deal**)malloc(sizeof(deal*) * 100);
}
void display_deal(deal deal)
{
    display_user(deal.sender);
    display_user(deal.receiver);
    printf("Item name: %s\n", deal.item_name);
    printf("Item weight: %.2f kg \n", deal.item_weight);
    printf("Deal code: %s\n", deal.deal_code);
    printDealStatus(deal.status);
}
void findDeal(const user* currentUser, const char* dealCode) 
{
    int found = 0;
    for (int i = 0; i < currentUser->number_of_deal; i++) 
    {
        deal* currentDeal = currentUser->deal_list[i];
        if (strcmp(currentDeal->deal_code, dealCode) == 0) 
        {
            display_deal(*currentDeal);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Invalid deal code. Deal not found.\n");
    }
}