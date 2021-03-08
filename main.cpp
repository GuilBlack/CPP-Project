#include "Track.h"

int main() {
    srand(time(NULL)); //gets seed for rand functions
    Track test = Track(); //create an obj track
    test.run(); //run the simulation
    cout << "write something and press enter to exit ^^";
    string end;
    cin >> end;
    return 0;
}