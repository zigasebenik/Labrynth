#include <iostream>
#include "MainClass.h"

using namespace std;

int main(int argc, char* argv[])

{
    MainClass* igra;
    igra = new MainClass(1600,1000);

    igra->gameloop();

    return 0;
}
