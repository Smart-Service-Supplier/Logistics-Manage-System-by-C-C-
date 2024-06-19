#include "data.h"



int user_choice()
{
    int choice;
    printf("1. Create a delivering deal.\n");
    printf("2. Check the deal\n");
    printf("3. List of the current available deal.\n");
    printf("4. Information of the app \n");
    scanf("%d", &choice);
    return choice;
}


int main()
{  
    printf("Hello, Welcome to logistics management system\n");
    user temp;
    printf(" Please tell give us some information \n");
    enter_user_infor(&temp);
    user sender;
    user_assign(&sender, temp);
    int choice = 0;
    while (1)
    {
        choice = user_choice();
        switch (choice)
        {
        case 1:
            {
                printf("You chose to create a delivering deal.\n");
                printf("Please enter the information of the receiver\n");
                user receiver;
                enter_user_infor(&temp);
                user_assign(&receiver, temp);
                deal myDeal;
                create_deal(&myDeal, &sender, &receiver);
                display_deal(myDeal);
                // free_memory(&receiver);
                continue;
            }
        case 2:
            {
                printf("Check the deal\n");
                printf("Please enter the deal code\n");
                char deal_code[11];
                scanf("%s", deal_code);
                find_Deal(&sender, deal_code);
                continue;
            }
        case 3:
            {
                printf("List of the current available deal.\n");
                print_all_user_deals(&sender);
                continue;
            }
        case 4:
            {
                printf("Information of the app \n");
                continue;
            }
        }
    }
    free_memory(&sender);
    return 0;
}