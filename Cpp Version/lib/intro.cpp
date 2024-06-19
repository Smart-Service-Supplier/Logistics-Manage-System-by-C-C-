#include "intro.hpp"

int Intro::display_1() {
    id = 1; 
    std::string t1 = "Intro.txt";
    std::string filename = DATA_PATH + t1;

    std::ifstream ifs(filename);

    std::string buffer; 
    while (std::getline(ifs, buffer)) {
        std::cout << buffer;
        Sleep(50);
    }
    std::cout << std::endl;
    std::cout << "Welcome to my Logistics-Manage-System !!!\n";
    return id; 
}

int Intro::loading() {
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed;
    // Do something time-consuming here
    while(elapsed.count() < 5)  {
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoading   " << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bLOading   " << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoAding   " << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoaDing   " << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoadIng   " << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoadiNg   " << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoadinG   " << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoading.  " << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoading.." << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoading..." << std::flush;
        Sleep(100);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
    }
    id = 0;
    std::cout << std::endl; 
    return id;
}