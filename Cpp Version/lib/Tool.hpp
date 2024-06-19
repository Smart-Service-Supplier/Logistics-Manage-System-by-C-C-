#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>
#include "config.h"

std::vector<std::string> splitString(std::string& str, char delimiter);
void deleteLine(const std::string& filename, int lineNumber);
bool stringCompare(std::string& str1, std::string& str2);
std::string generate_code();

int check_user(std::string &user);
bool check_password(std::string &password, int line_num);
void stringClean(std::string &str);
int check_deal(std::string &deal, std::string phone_number);