#include "Tool.hpp"

std::vector<std::string> splitString(std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

void deleteLine(const std::string& filename, int lineNumber) {
    std::ifstream fileIn(filename); // Open the file for reading
    if (!fileIn) {
        std::cerr << "Unable to open file for reading.\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    int currentLine = 0;

    // Read all lines from the file
    while (std::getline(fileIn, line)) {
        currentLine ++;
        if (currentLine != lineNumber) {
            lines.push_back(line);
        } 
    }

    fileIn.close();

    std::ofstream fileOut(filename); // Open the file for writing
    if (!fileOut) {
        std::cerr << "Unable to open file for writing.\n";
        return;
    }

    // Write all lines back to the file except the one to be deleted
    for (const auto& line : lines) {
        fileOut << line << "\n";
    }

    fileOut.close();
}

bool stringCompare(std::string& str1, std::string& str2) {
    if(str1[str1.length() - 1] == '\n') str1.pop_back();
    if(str2[str2.length() - 1] == '\n') str2.pop_back(); 
    if(str1.length() != str2.length()) return false; 
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) return false;
    }
    return true; 
}

std::string generate_code() {
    std::string character = "abcdefghiklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string code;
    int length = 10;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for(int i = 0; i < length; ++i)
    {
        int randomIndex = std::rand() % character.length();
        code += character[randomIndex];
    }
    return code;
}

int check_user(std::string &user) {
    std::string dataname = "Userdata.csv";
    std::string filename = DATABASE_PATH + dataname; 
    std::ifstream myfile(filename); 

    std::string line; 
    int current_line = 0;
    while (std::getline(myfile, line)) {
        current_line ++;
        std::vector<std::string> extract = splitString(line, ','); 
        // std::cout << extract[0] << std::endl;
        // std::cout << user << std::endl;
        // std::cout << user.length() << " " << extract[0].length() <<std::endl; 
        if (stringCompare(extract[0], user)) {
            myfile.close();
            return current_line;
        }
    }
    myfile.close();
    return 0; 
}

bool check_password(std::string &password, int line_num) {
    std::string dataname = "Userdata.csv";
    std::string filename = DATABASE_PATH + dataname; 
    std::ifstream myfile(filename); 

    std::string line; 
    int current_line = 0;
    while (std::getline(myfile, line)) {
        current_line ++;
        if (current_line == line_num) {
            std::vector<std::string> extract = splitString(line, ',');
            std::cout << password << std::endl;
            std::cout << extract[1] << std::endl;
            std::cout << password.length() << " " << extract[1].length() <<std::endl;
            if(stringCompare(extract[1], password)) return true; 
            else return false; 
        }
    }
    myfile.close();
    return false;
}

void stringClean(std::string &str) {
    while (str[str.length()-1] == '\n' or str[str.length()-1] == ' ') str.pop_back();
}

int check_deal(std::string &deal, std::string phone_number) {
    std::string filename = DATABASE_PATH + phone_number + ".csv"; 
    std::ifstream myfile(filename); 

    std::string line; 
    int current_line = 0;
    while (std::getline(myfile, line)) {
        current_line ++;
        std::vector<std::string> extract = splitString(line, ','); 
        std::cout << extract[0] << " " << extract[0].length() << std::endl; 
        std::cout << deal << " " << deal.length() << std::endl;

        if (stringCompare(extract[0], deal)) {
            myfile.close();
            return current_line;
        }
    }
    myfile.close();
    return 0; 
}
