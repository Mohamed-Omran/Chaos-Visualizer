#include "Program.h"
#include <windows.h>
int main(){

    Program demo;

    while (true) {
        demo.simulate();
        demo.updateInterface();
        Sleep(1000);
    }

    return 0;
}