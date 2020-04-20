#include "Program.h"
#include <windows.h>
int main(){

    Program demo;

    while (true) {
        demo.simulate();
        demo.updateInterface();
     //   Sleep(100);
    }

    return 0;
}