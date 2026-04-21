#include <cstdlib>
#include <ctime>
#include "ATM_UI.h"
using namespace std;
int main()
{
    //Seeding the random function
    srand(time(0));

    //Starting the App
    ATM_UI ATM;
    ATM.welcomeScreen();

    return 0;
}