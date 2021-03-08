//
// Created by guill on O4/O5/2O2O.
//
#include "Track.h"

//will print the circuit
void Track::printCircuit() {
    //loop through each coord
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 13; x++) {
            bool space = true;
            //loop through each track parts
            for (int i = 0; i < 50; i++) {
                //if it's a track print what needs to be printed
                if (circuit[i][0] == x && circuit[i][1] == y) {
                    if (i < 10) {
                        cout << " " << i << " ";
                    }else {
                        cout << i << " ";
                    }
                    space = false;
                    break;
                }
            }
            if (pitStop[0] == x && pitStop[1] == y) {
                space = false;
                cout << " P ";
            }
            if (space == true) {
                cout << "   ";
            }
        }
        cout << endl;
    }
}

//initialize all the cars
void Track::initCars() {
    //generates the users 1st car (can be improved)
    bool checkName1 = false;
    bool checkFuel1 = false;
    string userCar1Name;
    float userCar1Fuel;
    while (checkName1 != true || checkFuel1 != true) {
        cout << "input your car name (3 characters) here:";
        cin >> userCar1Name;
        cout << endl;
        if (userCar1Name.length() == 3) {
            checkName1 = true;
        } else {
            cout << "This username is invalid! Try again!" << endl;
            continue;
        }
        cout << "input your car fuel amount (more than 0 but less than 151) here:";
        cin >> userCar1Fuel;
        cout << endl;
        if (userCar1Fuel <= 0 || userCar1Fuel >= 151) {
            cout << "You didn't input a valid number! Try again!" << endl;
            userCar1Fuel = NULL;
            continue;
        } else {
            checkFuel1 = true;
        }
    }

    //generates the users 2nd car (can be improved)
    bool checkName2 = false;
    bool checkFuel2 = false;
    string userCar2Name;
    float userCar2Fuel;
    while (checkName2 != true || checkFuel2 != true) {
        cout << "input your car name (3 characters) here:";
        cin >> userCar2Name;
        cout << endl;
        if (userCar2Name.length() == 3) {
            checkName2 = true;
        } else {
            cout << "This username is invalid! Try again!" << endl;
            continue;
        }
        cout << "input your car fuel amount (more than 0 but less than 151) here:";
        cin >> userCar2Fuel;
        cout << endl;
        if (userCar2Fuel <= 0 || userCar2Fuel >= 151) {
            cout << "You didn't input a valid number! Try again!" << endl;
            userCar2Fuel = NULL;
            continue;
        } else {
            checkFuel2 = true;
        }
    }
    cout << "We will now proceed to the initialization of all the cars:" << endl;

    //generates the cars of the 2 users
    cars[20] = Car(userCar1Fuel, userCar1Name);
    cout << "Your first car name is: " << cars[20].getName() << " and its fuel amount is: " << cars[20].getFuel() << endl;
    cars[21] = Car(userCar2Fuel, userCar2Name);
    cout << "Your second car name is: " << cars[21].getName() << " and its fuel amount is: " << cars[21].getFuel() << endl;

//IMPORTANT LOOP TO CHANGE LATER
    //generates the random opponents
    for (int i = 0; i < 20; i++) {
        Track::cars[i] = Car();
        cout << cars[i].getName() << " fuel: " << cars[i].getFuel() << endl;
    }

}

//print the positioning of all the cars and the telemetries each 1.2s approx
void Track::printRaceState() {
    for (int j = 0; j < 22; j++) {
        for (int i = 0; i < 50; i++) {
            if (cars[j].getCoordX() == Track::circuit[i][0] && cars[j].getCoordY() == Track::circuit[i][1]) {
                if (j == 20 || j == 21) {
                    if (cars[j].isCarActive()) {
                        cars[j].displayTelemetries(i);
                    }else {
                        cout << cars[j].getName() << ": " << cars[j].getStatus() << endl;
                    }
                } else {
                    if (cars[j].isCarActive()) {
                        cout << cars[j].getName() << ": " << cars[j].getLap() << ":" << i << "; ";
                    }else {
                        cout << cars[j].getName() << ": " << cars[j].getStatus() << "; ";
                    }
                    if (j == 19) {
                        cout << endl;
                    }
                }
            }
        }
    }
}

//print the ranking table
void Track::finish() {
    cout << "This is the end of this simulation! hope you enjoyed it!" << endl;
    cout << "Ranking" << endl;
    for (int i = 1; i < 23; i++) {
        for (int j = 0; j < 22; j++) {
            if (cars[j].getRank() == i) {
                cout << "Rank " << i << ": " << cars[j].getName() << endl;
            }
        }
    }
}

//tells the user how many laps he wants to simulate
void Track::numberOfLaps() {
    bool choice = false;
    string lapNum;
    while (!choice) {
        cout << "please choose between 2, 5, 10, 25 or 50:" << endl;
        cin >> lapNum;
        if ((lapNum == "2") ||(lapNum == "5") || (lapNum == "10") || (lapNum == "25") || (lapNum == "50")) {
            laps = stoi(lapNum) + 1;
            cout << "you chose to do " << (laps - 1) << " laps!" <<endl;
            choice = true;
        }else {
            cout << "please input a valid number!" << endl;
        }
    }
}

void Track::run() {
    //init the simulation
    cout << "Hi man! This is the circuit on which your 2 cars will compete against 20 other cars!" << endl;
    cout << "The cars will do 50 laps (at max) in total and one lap is 5km371m. The top speed of all the cars are the same: 323km/h (353km/h with DRS on)." << endl;
    cout << "All of the pilots are novice... I hope they will do well!" << endl;
    cout << "ABS is banned from f1 racing so we took the privilege to disable it for you ^^" << endl;
    cout << "You will get to see the 10 telemetries of your two cars at each prints of the circuit:" << endl;
    printCircuit();
    cout << "each laps you will be prompt if you want to change some things in your cars so that there will not be any problems." << endl;
    cout << "Since our simulation is pretty accurate with the duration of a race, we will let you choose a specific number of laps so that it will not be too long..." << endl;
    numberOfLaps();
    cout << "You can choose some parameters for your car here (it's just the basic parameters. Oh and FOR THE SAKE OF GOD PLEASE DONT INPUT LETTERS IN THE FUEL AMOUNT):" << endl;
    initCars();

    cout << "The race starts NOW!" << endl;

    bool run = true;
    double doubleDuration = 0.41;
    int cornerType;
    int d = 0;
    //will run the simulation
    while (run) {
        //loop through all the track
        for (int i = 0; i < 50; i++) {
            //loop through all the cars
            for (int j = 0; j < 22; j++) {
                //see if there is a car in a specific part of the track
                if (cars[j].getCoordX() == Track::circuit[i][0] && cars[j].getCoordY() == Track::circuit[i][1]) {
                    if (!cars[j].isCarActive() || (cars[j].getStatus() == "finished")) {
                        continue;
                    }

                    if (!cars[j].isCheckPos()) {
                        // Check for upcoming corners (if car is within 2 'track segments' before the corner)
                        for (int k = 0; k < 9; k++) {
                            if ((allCorners[k] - i) <= 2 && (allCorners[k] - i) > 0) {
//                                CORNER INCOMING
                                if (k % 2 == 0) {
//                                    uTurn
                                    cars[j].brakeOrAccelerate(2, doubleDuration);  // Brake
                                } else {
//                                    sharp corner
                                    cars[j].brakeOrAccelerate(1, doubleDuration);  // Brake
                                }

                                break;
                            } else if (k == 8) {
                                cars[j].brakeOrAccelerate(0, doubleDuration);  // Accelerate
                            }
                        }

                        // Modify distance after a track segment has been passed
                        if (cars[j].getDistance() > 107.42) {
//                            distance-107.42 because our circuit is devided in 50 parts
//                            each parts is 107.42m precisely
                            cars[j].setDistance((cars[j].getDistance() - 107.42));
                            cars[j].setCoord(Track::circuit[(i + 1) % 50][0], Track::circuit[(i + 1) % 50][1]);
                            //see if the car has slowed down enough not to crash in a wall
                            for (int c = 0; c < 9; c++) {
                                if ((i+1) == allCorners[c]) {
                                    cornerType = c%2;
                                    cars[j].checkCrash(cornerType);
                                    break;
                                }
                            }
                            //see if he has finished a lap
                            if (cars[j].getCoordX() == 3 && cars[j].getCoordY() == 4) {
                                //next lap
                                cars[j].increaseLap();
                                //see if the car has finished the race
                                if (cars[j].getLap() == laps) {
                                    cout << "-----------" << endl;
                                    cars[j].setFinished("finished", rank);
                                    cout << "-----------" << endl;
                                    Track::rank++;
                                    continue;
                                }
                                //see if it's a bot or the user
                                //if it's a bot, it will change the car's parts automatically
                                //if it's the user, it will wait for his choice
                                if (j == 20 || j == 21) {
                                    cars[j].userChangeParts();
                                    cout << "-----------" << endl;
                                    cars[j].displayTelemetries(i+1);
                                    cout << "-----------" << endl;
                                }else {
                                    cars[j].autoChangeParts();
                                }
                            }
                            //if we dont set in on, it will also set a new distance the next loop. it's due to the order of the loops
                            //could improve
                            cars[j].setCheckPos(true);
                        }
                        //check if the car is functioning correctly
                        cars[j].breakDown();
                    }
                }
            }
        }

        //print the state of the race
        if (d%3 == 0) {
            cout << "---------------------" << endl;
            printCircuit();
            printRaceState();
            cout << "---------------------" << endl;
        }

        //reset the check pos if not, the car will not be able to move
        for (int k = 0; k < 22; k++) { //IMPORTANT LOOP
            cars[k].setCheckPos(false);
        }

        //see if all the cars have finish the race to exit the while loop
        for (int f = 0; f < 22; f++) {
            if (cars[f].isCarActive()) {
                run = true;
                break;
            }else {
                run = false;
            }
        }
        //the d var is just here
        ++d;
        this_thread::sleep_for(0.4s);
    }

    //display the ranking
    finish();
}








