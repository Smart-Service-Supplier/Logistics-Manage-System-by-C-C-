#include "screen.hpp"
#define BUFFER_SIZE 256

Screen::Screen(screen_type id) {
    this->id = id;
}

void Screen::display_login(User* user) {
    char ans; 
    std::cout << "Have you had account ? Y/N" << std::endl;
    std::cin >> ans; 
    std::cin.ignore();

    if (ans == 'Y' or ans == 'y') {
        std::string Username;
        std::string Password;   

        std::cout << "Enter your username: ";
        getline(std::cin, Username);
        stringClean(Username);

        int line_num = check_user(Username);
        if (line_num == 0) {
            this->id = LOGIN;
            std::cout << "INVALID USERNAME !!!\n";
            Sleep(3000);
            return;  
        } 

        std::cout << "Enter password: "; 
        std::cin >> Password;
        if (Password[Password.length() - 1] == '\n') Password.pop_back();
        if (check_password(Password, line_num) == false) {
            this->id = LOGIN; 
            std::cout << "INVALID PASSWORD !!!\n";
            Sleep(3000);
            return; 
        }

        this->id = HOME; 

        std::string dataname = "Userdata.csv";
        std::string filename = DATABASE_PATH + dataname; 
        std::ifstream myfile(filename); 

        std::string line; 
        int current_line = 0;
        while (std::getline(myfile, line)) {
            current_line ++;
            if (current_line == line_num) {
                std::vector<std::string> extract = splitString(line, ',');
                user->setAccount(Username);
                user->setPassword(Password);
                user->setName(extract[2]);
                user->setPhoneNumber(extract[3]);
                user->address.city = extract[4];
                user->address.province = extract[5];
                user->address.ward = extract[6];
                user->address.street_name = extract[7];
                user->address.address_in_detail = extract[8];
            }
        }
        
    }
    else this->id = CRE_USER;
    
}

void Screen::display_create_user(User *user) {
    std::cout << "Registering new user..." << std::endl;

    std::string buffer; 
   
    std::string dataname = "Userdata.csv";
    std::string filename = DATABASE_PATH + dataname; 
    std::ofstream myfile; 
    myfile.open(filename, std::ios_base::app);

    std::cout << "Username: "; 
    getline(std::cin, buffer);
    stringClean(buffer);
    myfile << buffer << ',';
    user->setAccount(buffer);

    std::cout << "Password: ";
    getline(std::cin, buffer);
    if(buffer[buffer.length() - 1] == '\n') buffer.pop_back();
    myfile << buffer << ',';
    user->setPassword(buffer);

    std::cout << "Name: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    myfile << buffer << ',';
    user->setName(buffer);

    std::cout << "Phone Number: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    myfile << buffer << ',';

    std::cout << "Enter Your Address: \n";
    std::cout << "City: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    myfile << buffer << ',';

    std::cout << "Province: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    myfile << buffer << ',';

    std::cout << "Ward: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    myfile << buffer << ',';

    std::cout << "Street: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    myfile << buffer << ',';

    std::cout << "Detailed Address: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    myfile << buffer << std::endl;

    this->id = LOGIN; 
}

void Screen::display_home() {// main screen
    int choice = 0;

    std::cout << "1. Create a new deal" << std::endl;
    std::cout << "2. Manage deals" << std::endl;
    std::cout << "3. Change Password" << std::endl;
    std::cout << "4. Log out" << std::endl;

    std::cout << "Enter your choice: "; 
    std::cin >> choice; 

    if(choice == 1) this->id = CUSTOMER;
    else if (choice == 2) this->id = MANAGE_DEAL;
    else if (choice == 3) this->id = EDIT_INFOR;
    else if (choice == 4) this->id = LOGIN;
    else this->id = LOGIN;
    std::cin.ignore();
} 

// Create a new deal
void Screen::display_customer_input(Deal *deal) {
    std::cout << "Creating a new deal ..." << std::endl;
    std::string code_deal = generate_code();
    deal->setCode(code_deal);

    deal->type = false;  
    
    std::cout << "Enter the receiver: " << std::endl;
    
    std::string buffer;

    std::cout << "Receiver name: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    deal->receiver->setName(buffer);

    std::cout << "Phone number: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    deal->receiver->setPhoneNumber(buffer);

    std::cout << "Enter Address: " << std::endl;

    std::cout << "City: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    deal->address->city = buffer;

    std::cout << "Province: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    deal->address->province = buffer;
    
    std::cout << "Ward: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    deal->address->ward = buffer;

    std::cout << "Street: ";
    getline(std::cin, buffer);
    stringClean(buffer);
    deal->address->street_name = buffer;

    std::cout << "Detailed Address: " << std::endl;
    getline(std::cin, buffer);
    stringClean(buffer);
    deal->address->address_in_detail = buffer;

    this->id = ITEM;
}

void Screen::display_item_input(Deal *deal) {
    std::cout << "Creating a new deal ..." << std::endl;
    std::cout << "Enter List of items: " << std::endl;
    std::cout << "Number of items: " << std::endl;
    int quantity; 
    std::cin >> quantity;
    std::cin.ignore();

    std::string buffer; 

    for (int i = 0; i < quantity; i++) {
        Item* temp = new Item();
        std::cout << "Item " << i + 1 << ":\n";

        std::cout << "Name: ";
        getline(std::cin, buffer);
        stringClean(buffer);
        temp->setName(buffer);

        std::cout << "Weight: ";
        getline(std::cin, buffer);
        stringClean(buffer);
        temp->setWeight(stod(buffer));

        std::cout << "Is the item Fragile? (Y/N): ";
        getline(std::cin, buffer);
        stringClean(buffer);
        if (buffer[0] == 'Y') temp->setIsFragile(true);
        else if (buffer[0] == 'N') temp->setIsFragile(false);
        else temp->setIsFragile(true);

        deal->list.push_back(*temp);
        delete temp;
    }

    deal->fee = 50200;

    this->clear();
    deal->display();
    deal->Self_update();
    Sleep(5000);

    this->id = HOME;
}

// Deal Manager
void Screen::display_manage_deal() {
    std::cout << "Managing deal" << std::endl;

    std::cout << "1. Receiving Deal List" << std::endl;
    std::cout << "2. Sending Deal List" << std::endl;
    std::cout << "3. Delete Deal" << std::endl;
    std::cout << "4. Go to Home" << std::endl;

    int choice; 
    std::cout << "Enter your choice: "; 
    std::cin >> choice;
    std::cout << choice << std::endl;

    if(choice == 1) this->id = RECV_LIST;
    else if (choice == 2) this->id = SEND_LIST;
    else if (choice == 3) this->id = DEAL_ACTION;
    else if (choice == 4) this->id = HOME;
    std::cin.ignore();
}

void Screen::display_recv_deal_list(User *admin) {
    std::vector<Deal> list;
    std::string buffer;

    std::string filename = DATABASE_PATH + admin->getPhoneNumber() + ".csv";
    std::ifstream myfile(filename);
    while (getline(myfile, buffer)) {// read data 
        std::vector<std::string> line = splitString(buffer,',');
        Deal deal;
        deal.setCode(line[0]);
        deal.type = (stoi(line[1]) ? true : false);

        if (deal.type == true) {// receive
            deal.receiver->setName(admin->getName());
            deal.receiver->setPhoneNumber(admin->getPhoneNumber());

            deal.sender->setName(line[2]);
            deal.sender->setPhoneNumber(line[3]);
        }
        else continue; 

        int j = 5; 
        for (int i = 0; i < stoi(line[4]); i++) {
            Item temp(line[j], stod(line[j+1]));
            bool b = (stoi(line[j+2]) ? true : false);
            deal.list.push_back(temp);
            j = j + 3;
        }

        deal.address->address_in_detail = line[j]; j++;
        deal.address->street_name = line[j]; j++;
        deal.address->ward = line[j]; j++;
        deal.address->province = line[j]; j++;
        deal.address->city = line[j]; j++;

        deal.fee = stoi(line[j]); j++; 
        deal.status = (DealStatus)stoi(line[j]);

        list.push_back(deal);
    }
    myfile.close();

    if(list.empty()) {
        std::cout << "There is no deal" << std::endl;
        Sleep(3000);
        this->id = MANAGE_DEAL;
        return;
    }

    // Showing
    std::cout << "List of receiving-deal codes:\n";
    for (int i = 0; i < list.size(); i++) {
        std::cout << i + 1 << ". " << list[i].getCode() << std::endl;
    }

    std::cout << "Enter a code for checking: "; 
    // std::cin.ignore();
    getline(std::cin, buffer);
    stringClean(buffer);

    for (int i = 0; i < list.size(); i++) {
        std::string temp = list[i].getCode();
        if(stringCompare(buffer, temp)) {
            this->clear();
            list[i].display();
            getchar();
            this->id = MANAGE_DEAL;
            return;
        }
    }
}
void Screen::display_send_deal_list(User *admin) {
    std::vector<Deal> list;
    std::string buffer;

    std::string filename = DATABASE_PATH + admin->getPhoneNumber() + ".csv";
    std::ifstream myfile(filename);
    Debug;
    while (getline(myfile, buffer)) {// read data 
        std::vector<std::string> line = splitString(buffer,',');
        Deal deal;
        deal.setCode(line[0]);
        deal.type = (stoi(line[1]) ? true : false);

        if (deal.type == false) {// receive
            deal.sender->setName(admin->getName());
            deal.sender->setPhoneNumber(admin->getPhoneNumber());

            deal.receiver->setName(line[2]);
            deal.receiver->setPhoneNumber(line[3]);
        }
        else continue; 

        int j = 5; 
        for (int i = 0; i < stoi(line[4]); i++) {
            Item temp(line[j], stod(line[j+1]));
            bool b = (stoi(line[j+2]) ? true : false);
            deal.list.push_back(temp);
            j = j + 3;
        }

        deal.address->address_in_detail = line[j]; j++;
        deal.address->street_name = line[j]; j++;
        deal.address->ward = line[j]; j++;
        deal.address->province = line[j]; j++;
        deal.address->city = line[j]; j++;

        deal.fee = stoi(line[j]); j++; 
        deal.status = (DealStatus)stoi(line[j]);

        list.push_back(deal);
    }
    myfile.close();
    if(list.empty()) {
        std::cout << "There is no deal" << std::endl;
        Sleep(3000);
        this->id = MANAGE_DEAL;
        return;
    }
    // Showing
    std::cout << "List of receiving-deal codes:\n";
    for (int i = 0; i < list.size(); i++) {
        std::cout << i + 1 << ". " << list[i].getCode() << std::endl;
    }

    std::cout << "Enter a code for checking: "; 
    // std::cin.ignore();
    getline(std::cin, buffer);
    stringClean(buffer);

    for (int i = 0; i < list.size(); i++) {
        std::string temp = list[i].getCode();
        if(stringCompare(buffer, temp)) {
            this->clear();
            list[i].display();
            getchar();
            this->id = MANAGE_DEAL;
            return;
        }
    }
}

void Screen::display_deal_action(User* admin) {
    std::vector<Deal> list;
    std::string buffer;

    std::string filename = DATABASE_PATH + admin->getPhoneNumber() + ".csv";
    std::ifstream myfile(filename);
    while (getline(myfile, buffer)) {// read data 
        std::vector<std::string> line = splitString(buffer,',');
        Deal deal;
        deal.setCode(line[0]);
        deal.type = (stoi(line[1]) ? true : false);

        if (deal.type == false) {// receive
            deal.sender->setName(admin->getName());
            deal.sender->setPhoneNumber(admin->getPhoneNumber());

            deal.receiver->setName(line[2]);
            deal.receiver->setPhoneNumber(line[3]);
        }
        else {
            deal.receiver->setName(admin->getName());
            deal.receiver->setPhoneNumber(admin->getPhoneNumber());

            deal.sender->setName(line[2]);
            deal.sender->setPhoneNumber(line[3]);
        } 

        int j = 5; 
        for (int i = 0; i < stoi(line[4]); i++) {
            Item temp(line[j], stod(line[j+1]));
            bool b = (stoi(line[j+2]) ? true : false);
            deal.list.push_back(temp);
            j = j + 3;
        }

        deal.address->address_in_detail = line[j]; j++;
        deal.address->street_name = line[j]; j++;
        deal.address->ward = line[j]; j++;
        deal.address->province = line[j]; j++;
        deal.address->city = line[j]; j++;

        deal.fee = stoi(line[j]); j++; 
        deal.status = (DealStatus)stoi(line[j]);

        list.push_back(deal);
    }
    myfile.close();
    if(list.empty()) {
        std::cout << "There is no deal" << std::endl;
        Sleep(3000);
        this->id = MANAGE_DEAL;
        return;
    }
    
    std::cout << "Enter Code of the deal to delete: ";
    std::cin.ignore();
    getline(std::cin, buffer);
    stringClean(buffer);
    
    int line = check_deal(buffer, admin->getPhoneNumber());
    if (line == 0) {
        std::cout << "Invalid deal code !!!";
        Sleep(2000);
        this->id = MANAGE_DEAL; 
        return;
    }
    else {
        for (int i = 0; i < list.size(); i++) {
            std::string temp = list[i].getCode();
            if(stringCompare(buffer, temp)) {
                list[0].Self_delete();
                this->id = MANAGE_DEAL;
                return; 
            }
        }
    }

    
}

// Edit User Information
void Screen::display_edit_infor(User *admin) {
    std::string buffer;
    std::cin.ignore();
    std::cout << "Changing password..." << std::endl;
    std::cout << "Please enter your current password: ";
    getline(std::cin, buffer);
    std::string user = admin->getAccount();
    if (check_password(buffer, check_user(user))) {
        std::string temp; 
        std::cout << "Please enter your new password: " ;
        getline(std::cin, temp);

        std::cout << "Re-enter your new password: ";
        getline(std::cin, buffer);

        if (stringCompare(buffer, temp)) {
            std::cout << "Change password successful"; 
            this->id = HOME; 

        } 
        else {
            this->id = EDIT_INFOR;
            return; 
        }
    }
}

void Screen::clear() {
    system("cls");
}

void Screen::display_handle_message(screen_type id) {

}