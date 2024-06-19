#include <iostream>
#include <chrono>
#include <windows.h>
#include <fstream>
#include <string>
#include "config.h"

class Intro {
    protected: 
        int id = 0; 
    public: 
        int display_1();
        int loading();
        int get_id(); 
};

