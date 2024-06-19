#include "data.h"

const char* deal_status_strings[] =
{
    "at_sender",
    "in_transfer",
    "at_warehouse",
    "shipping",
    "at_receiver"
};

void printDealStatus(deal_status status) 
{
    if (status >= at_sender && status <= at_receiver) 
    {
        printf("Deal Status: %s\n", deal_status_strings[status]);
    } else {
        printf("Invalid Deal Status\n");
    }
}

void free_memory(user* currentUser) 
{
    for (int i = 0; i < currentUser->number_of_deal; i++) 
    {
        free(currentUser->deal_list[i]);  // Giải phóng deal
    }
    free(currentUser->deal_list);  // Giải phóng mảng con trỏ deals
}

void user_assign(user* user_dest, user user_source)
{
    strcpy(user_dest->name, user_source.name);
    strcpy(user_dest->phone_number, user_source.phone_number);
    strcpy(user_dest->address_user.province, user_source.address_user.province);
    strcpy(user_dest->address_user.city, user_source.address_user.city);
    strcpy(user_dest->address_user.ward, user_source.address_user.ward);
    strcpy(user_dest->address_user.street_name, user_source.address_user.street_name);
    strcpy(user_dest->address_user.address_number, user_source.address_user.address_number);
    user_dest -> number_of_deal = 0;
    user_dest ->deal_list = (deal**)malloc(sizeof(deal*) * MAX_DEALS);
}

void enter_user_infor(user* User_input)
{
    fflush(stdin);
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
void display_user(user user)
{
    printf("Name: %s\n", user.name);
    printf("Phone Number: %s\n", user.phone_number);
    printf("Province: %s\n", user.address_user.province);
    printf("City: %s\n", user.address_user.city);
    printf("Ward: %s\n", user.address_user.ward);
    printf("Street name: %s\n", user.address_user.street_name);
    printf("Address number: %s\n", user.address_user.address_number);
    // printf("Number of available deal: %d \n", user.number_of_deal);
}

void generateCode(char* code) {
    srand(time(NULL)); 

    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int charsetSize = sizeof(charset) - 1; 
    for (int i = 0; i < 10; i++) {
        int randomIndex = rand() % charsetSize; 
        code[i] = charset[randomIndex]; 
    }

    code[10] = '\0'; 
}

void display_deal(deal deal)
{
    printf("Information of Sender:\n");
    display_user(deal.sender);
    printf("Information of Receiver:\n");
    display_user(deal.receiver);
    printf("Item name: %s\n", deal.item_name);
    printf("Item weight: %.2f kg \n", deal.item_weight);
    printf("Deal code: %s\n", deal.deal_code);
    printDealStatus(deal.status);
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

void find_Deal(const user* currentUser, const char* dealCode) 
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
void print_all_user_deals(const user* currentUser) {
    if (currentUser->number_of_deal == 0) {
        printf("No deals found for this user.\n");
        return;
    }

    printf("User: %s\n", currentUser->name);
    printf("Number of deals: %d\n", currentUser->number_of_deal);

    for (int i = 0; i < currentUser->number_of_deal; i++) {
        deal* currentDeal = currentUser->deal_list[i];
        printf("Deal %d:\n", i+1);
        printf("Sender:\n");
        display_user(currentDeal->sender);
        printf("Receiver:\n");
        display_user(currentDeal->receiver);
        printf("Item name: %s\n", currentDeal->item_name);
        printf("Item weight: %f\n", currentDeal->item_weight);
        printf("Deal code: %s\n", currentDeal->deal_code);
        printDealStatus(currentDeal->status);
    }
}