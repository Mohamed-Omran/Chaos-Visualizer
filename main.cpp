#include "Program.h"
#include <windows.h>
int main(){

    Program demo;

    while (true) {
       
        demo.updateInterface();
        demo.simulate();
        //Sleep(10);
    }

    return 0;
}