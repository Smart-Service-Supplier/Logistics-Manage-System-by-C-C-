#include "Objects.hpp"
#include <iostream>

// Mehtods for Item class
Item::Item(std::string name, double weight) {
    this->name = name;
    this->weight = weight;
}

void Item::setName(std::string name) {
    this->name = name;
}

void Item::setWeight(double weight) {
    this->weight = weight;
}
void Item::setIsFragile(bool isFragile) {
    this->fragile = isFragile;
}

bool Item::isFragile() {
    return this->fragile;
}

std::string Item::getName() {
    return this->name;
}

double Item::getWeight() {
    return this->weight;
}

void Item::display() {
    std::cout << this->name << ", " << this->weight << " kg" << ", " << (this->fragile ? "is fragile" : "is not fragile") << std::endl;
}
// End Item class

// Methods for Deal class
void Deal::setCode(std::string code) {
    this->code = code;
}

std::string Deal::getCode() {
    return this->code;
}

void Deal::display() {
    std::cout << "Deal " << this->code << std::endl;
    std::cout << "Sent from " << this->sender->getName() << " to " << this->receiver->getName() << std::endl;
    std::cout << "Deal contains " << this->list.size() << ((this->list.size() == 1) ? " item" : " items") << std::endl; 
    for (int i = 0; i < this->list.size(); i++) {
        std::cout << "Item " << i + 1 << ": ";
        this->list[i].display();
    }
    
    std::cout << "To: " << this->address->address_in_detail << ", " << this->address->street_name << ", " << this->address->ward << ", " << this->address->province
        << ", " << this->address->city << std::endl; 

    std::cout << "Fee: " << this->fee << " VND" << std::endl << std::endl;

    std::cout << "THE STATUS OF THE DEAL: " << STATUS[(int)this->status] << std::endl;
}
/*
bool type; 
BasicUser partner;
BasicUser Owner; 
Address address;
std::vector<Item> list;
int fee; 
*/
void Deal::Self_update() {
    // Receiving deal
    std::string filename = DATABASE_PATH + this->receiver->getPhoneNumber() + ".csv";
    std::ofstream rFile; 
    rFile.open(filename, std::ios_base::app);
    rFile << this->code << ','; 
    rFile << (!this->type) << ',';
    rFile << this->sender->getName() << ',';
    rFile << this->sender->getPhoneNumber() << ','; 
    rFile << this->list.size();

    if (list.size() == 0) rFile << ',';

    for (int i = 0; i < this->list.size(); i++) {
        rFile << ',';
        rFile << this->list[i].getName() << ',';
        rFile << this->list[i].getWeight() << ',';
        rFile << this->list[i].isFragile();
    }

    if(list.size() != 0) rFile << ',';

    rFile << this->address->address_in_detail << ',';
    rFile << this->address->street_name << ',';
    rFile << this->address->ward << ',';
    rFile << this->address->province << ',';
    rFile << this->address->city << ',';

    rFile << this->fee << ',';

    rFile << this->status << std::endl;

    rFile.close();
    
    // Sending deal
    filename = DATABASE_PATH + this->sender->getPhoneNumber() + ".csv";
    std::ofstream sFile; 
    sFile.open(filename, std::ios_base::app);
    sFile << this->code << ','; 
    sFile << this->type << ',';
    sFile << this->receiver->getName() << ',';
    sFile << this->receiver->getPhoneNumber() << ','; 
    sFile << this->list.size();

    if (list.size() == 0) sFile << ',';

    for (int i = 0; i < this->list.size(); i++) {
        sFile << ',';
        sFile << this->list[i].getName() << ',';
        sFile << this->list[i].getWeight() << ',';
        sFile << this->list[i].isFragile();
    }

    if(list.size() != 0) sFile << ',';

    sFile << this->address->address_in_detail << ',';
    sFile << this->address->street_name << ',';
    sFile << this->address->ward << ',';
    sFile << this->address->province << ',';
    sFile << this->address->city << ',';

    sFile << this->fee << ',';

    sFile << this->status << std::endl;
    
    sFile.close();
}

void Deal::Self_delete() {
    std::string filename = DATABASE_PATH + this->receiver->getPhoneNumber() + ".csv";
    std::ifstream myfile(filename);

    int delete_line = 0; 
    std::string line;

    bool valid = false; 
    while (std::getline(myfile, line)) {// find the line to delete
        delete_line++;
        if (line[line.length() - 1] == '\n') line.pop_back();
        std::vector<std::string> extract = splitString(line, ',');
        if (stringCompare(extract[0], this->code)) {
            valid = true; 
            myfile.close();
            break;
        }
    }
    if (valid == true) deleteLine(filename, delete_line);

    if (this->type == false) {
        valid = false; 
        std::string filename = DATABASE_PATH + this->sender->getPhoneNumber() + ".csv";
        std::ifstream myfile(filename);

        int delete_line = 0; 
        std::string line;

        while (std::getline(myfile, line)) {// find the line to delete
            delete_line++;
            if (line[line.length() - 1] == '\n') line.pop_back();
            std::vector<std::string> extract = splitString(line, ',');
            if (stringCompare(extract[0], this->code)) {
                valid = true;
                myfile.close();
                break;
            }
        }
        if (valid == true) deleteLine(filename, delete_line); 
    }
}

void Deal::Self_update_status() {
    std::string code = this->code;

    std::string filename1 = DATABASE_PATH + this->receiver->getPhoneNumber() + ".csv";
    std::string filename2 = DATABASE_PATH + this->sender->getPhoneNumber() + ".csv";

    int line_send = check_deal(code, this->sender->getPhoneNumber());
    int line_recv = check_deal(code, this->receiver->getPhoneNumber());

    std::vector<std::string> lines;
    std::string buffer;  

    // Update status on sender side
    int i = 0; 
    std::ifstream file2(filename2);
    while(getline(file2, buffer)) {
        i++; 
        if (i == line_send) {
            std::vector<std::string> extract = splitString(buffer, ',');
            DealStatus new_state = ((DealStatus)(stoi(extract[extract.size() - 1])) == FINISHED) ? FINISHED : DealStatus(stoi(extract[extract.size() - 1]) + 1);

            buffer = "";
            buffer.push_back((int)new_state + '0');
            extract[extract.size() - 1] = buffer; 

            buffer = "";
            for (int i = 0; i < extract.size(); i++) buffer += extract[i] + ',';
            buffer.pop_back(); // delete the last ','
        }
        lines.push_back(buffer);
    }
    file2.close();

    std::ofstream edited_sender;
    edited_sender.open(filename2, std::ios_base::out);
    for (int i = 0; i < lines.size(); i++) edited_sender << lines[i] << std::endl; 

    // Update Status on receiver side 
    i = 0; 
    std::ifstream file1(filename1);
    while(getline(file1, buffer)) {
        i++; 
        if (i == line_send) {
            std::vector<std::string> extract = splitString(buffer, ',');
            DealStatus new_state = ((DealStatus)(stoi(extract[extract.size() - 1])) == FINISHED) ? FINISHED : DealStatus(stoi(extract[extract.size() - 1]) + 1);

            buffer = "";
            buffer.push_back((int)new_state + '0');
            extract[extract.size() - 1] = buffer; 

            buffer = "";
            for (int i = 0; i < extract.size(); i++) buffer += extract[i] + ',';
            buffer.pop_back(); // delete the last ','
        }
        lines.push_back(buffer);
    }
    file2.close();

    std::ofstream edited_receiver;
    edited_receiver.open(filename1, std::ios_base::out);
    for (int i = 0; i < lines.size(); i++) edited_receiver << lines[i] << std::endl; 
}

// End Deal class

// Methods for User class

std::string User::getAccount() {
    return this->account;
}

std::string User::getPassword() {
    return this->password;
}

void User::setAccount(std::string account) {
    this->account = account;
}

void User::setPassword(std::string password) {
    this->password = password;
}
// End User class





// int main () {
//     Deal* mydeal = new Deal;
//     mydeal->setCode("12122004");
//     std::cout << mydeal->getCode() << std::endl;

//     mydeal->address = new Address("Ba Dinh", "Hanoi", "Dien Bien", "Cao Ba Quat", "So 3");
//     mydeal->sender = new BasicUser("Nguyen Cao Minh", "0336122004");
//     mydeal->receiver = new BasicUser("Cao Minh Junior", "0336122006");
//     mydeal->type = false; 
//     mydeal->fee = 1314000;
    
//     Item* item = new Item("Heart", 1314);
//     item->setIsFragile(true);

//     mydeal->list.push_back(*item);

//     mydeal->list[0].display();
//     mydeal->status = FINISHED;
    
//     mydeal->display();
//     // mydeal->Self_update();
//     mydeal->Self_delete();

//     std::string a = "12122004"; 
//     std::string b = "12122005";

//     std::cout << stringCompare(a, b) << std::endl;
// }