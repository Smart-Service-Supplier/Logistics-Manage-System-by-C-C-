#include <iostream>
#include "../lib/intro.hpp"

int main(int argc, char **argv) {
    while (true) {
        Introduction *e = new Introduction;  
        e->loading(); 
        e->display_1();
        delete e; 
        break; 
    }
    return 0; 
}