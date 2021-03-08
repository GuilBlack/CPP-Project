//
// Created by guill on O4/O5/2O2O.
//
#include "Car.h"

using namespace std;

//constructor
Car::Car(float fuelAmount, string carName, int ABS) {
    fuel = fuelAmount;
    name = carName;
    antiLockBS = ABS;
}

//as the name implies
const string Car::getName() const {
    return name;
}

//as the name implies
int Car::getCoordX() {
    return coord[0];
}

//as the name implies
int Car::getCoordY() {
    return coord[1];
}

//see how many laps has passed
int Car::getLap() {
    return lap;
}

//so that the car can move on the track
void Car::setCoord(int x, int y) {
    coord[0] = x;
    coord[1] = y;
}

//generates a random name for bot cars
string Car::randomName() {
    int r;
    char c;
    string name;
    for (int i = 0; i < 3; i++) {
        r = rand() %26;
        c = (char)(r + 65);
        name += c;
    }
    return name;
}

//as the name implies
float Car::getFuel() const {
    return fuel;
}

//as the name implies
double Car::getDistance() const {
    return distance;
}

//so that the distance will not have logical errors when traveling from 1 part of the circuit to another
void Car::setDistance(double distance) {
    Car::distance = distance;
}

//see how much the pilot can accelerate... the randomness represents the pilot's competence
void Car::accelerationRandom() {
    int prevAcc = acceleration;
    int calculatedMaxAcc = (int)(MAX_ACCELERATION*accCoef);
    if (acceleration < calculatedMaxAcc) {
        int range = calculatedMaxAcc - acceleration;
        Car::acceleration = rand() % range + prevAcc;
    }
    else{
        Car::acceleration = prevAcc;
    }
//    cout << "accCoef: "<< accCoef << " calculatedMaxAcc: " << calculatedMaxAcc << endl;
}

//see how much the pilot can decelerate... the randomness represents the pilot's competence
void Car::decelerationRandom() {
    int prevDec = deceleration;
    Car::calculatedMaxDec = (int)(MAX_DECELERATION*decCoef);
    if (deceleration < calculatedMaxDec) {
        int range = calculatedMaxDec - deceleration;
        Car::deceleration = rand() % range + prevDec;
    } else {
        Car::deceleration = prevDec;
    }
}

//see how much the speed increase of decrease
//has a direct relationship with the acceleration/deceleration
void Car::speedVariation(int x) {
    //if 0 -> accelerate; if 1 -> slow for a corner; if 2 ->slow down for a uturn
    if (x == 0) {
        //max speed can change if the drs is on or not
        if (DRS) {
            maxSpeed = 335;
        } else {
            maxSpeed = 323;
        }
        //MORE SPEED
        if ((speed + acceleration) < maxSpeed) {
            speed += acceleration;
        } else {
            speed = maxSpeed;
        }
    }else {
        //LESS SPEED
        if (x == 1) {
            if ((speed - deceleration) > 125) {
                speed -= deceleration;
            } else {
                speed = 125;
            }
        } else {
            if ((speed) - deceleration > 85) {
                speed -= deceleration;
            } else {
                speed = 85;
            }
        }
    }
}

//simple physics d = s*t
void Car::changeDistance(double duration) {
    speedMS = speed / 3.6;
    distance += speedMS * duration;
}

//so that there is no confusion if the car goes up 1 position in the track
bool Car::isCheckPos() const {
    return checkPos;
}

//so that there is no confusion if the car goes up 1 position in the track
void Car::setCheckPos(bool checkPos) {
    Car::checkPos = checkPos;
}

//calculate turbo pressure (has a direct relationship with speed)
void Car::calculateEngineStats() {
    Car::engineTemp = (speed/maxSpeed)*290;
    if (Car::engineTemp > 220) {
        Car::engineWear += 0.005;
    }
//    cout <<  "engineWear: " << engineWear << " engineTemp: " << engineTemp << endl;
}

//calculate turbo pressure (has a direct relationship with speed)
void Car::calculateTurboPressure() {
    Car::turboPressure = (speed/maxSpeed)*3.5;
//    cout <<  "turbo: " << turboPressure << endl;
}

//calculate a coef for the acceleration of the car (to have a deceleration limit) with:
//engine wear, turbo pressure and tyre pressure
void Car::calculateAccCoef() {
    Car::accCoef = 1;
    float tempoTurboPressure = (turboPressure/TURBO_PRESSURE_MAX)*0.3; //scale it down to between 0 and 0.3
    float tempoEngineWear = (engineWear/100)*(-1);
    float tempoTyrePressure = ((21.5 - tyrePressure)/21.5)*(-1);

    accCoef += ((tempoTurboPressure) + (tempoEngineWear) + (tempoTyrePressure));
}

//the name says it all
void Car::calculateTyreWear() {
    tyreWear += 0.0005;
}

//the name says it all
void Car::calculateTyrePressure() {
    tyrePressure -=0.0001;
}

//the name says it all
void Car::calculateTyreWearInBrake() {
    tyreWear += 0.005;
}

//the name says it all
void Car::calculateBrakeWear() {
    Car::brakeWear += 0.01;
}

//calculate how many laps a car did
void Car::increaseLap() {
    Car::lap +=1;
//    cout << "lap: " << lap << endl;
}

//calculate fuel level in the race
void Car::calculateFuel() {
    Car::fuel -= 0.075;
//    cout << "fuel: " << fuel << endl;
}

//calculates the brake temp with the speed and the deceleration of the car as parameter.
void Car::calculateBrakeStats() {
    Car::brakeTemp = ((speed*(float)(deceleration))/(maxSpeed*(float)(calculatedMaxDec)))*1200;
//    cout <<  "brakeWear: " << brakeWear << " brakeTemp: " << brakeTemp << endl;
}

//calculate a coef for the deceleration of the car (to have a deceleration limit) with:
//tyre pressure brake wear and the brake temperature
void Car::calculateBrakeCoef() {
    Car::decCoef = 1;
    float tempoTyrePressure = ((21.5 - tyrePressure)/21.5)*(-1);
    float tempoBrakeWear = (brakeWear/100)*(-1);
    if (brakeTemp >= 500 && brakeTemp < 1000) {
        Car::decCoef += ((tempoTyrePressure) + (tempoBrakeWear) + 0.35);
    } else {
        Car::decCoef += ((tempoTyrePressure) + (tempoBrakeWear));
    }
//    cout << "brake coef: " << decCoef << endl;
}

//choose whether we need to brake or accelerate
void Car::brakeOrAccelerate(int x, double duration) {
    calculateFuel();
    calculateTyreWear();
    calculateTyrePressure();
//    cout << "Tyre Wear: " << tyreWear << endl;
    if (x == 0) {
        deceleration = 0;
//        cout << "Accelerating..." << endl;
        calculateTurboPressure();
        calculateEngineStats();
        calculateAccCoef(); // accelerate
        accelerationRandom();
    } else {
        acceleration = 0;
//        cout << "Braking..." << endl;
        calculateBrakeWear();
        calculateBrakeStats();
        calculateTyreWearInBrake();
        calculateBrakeCoef();
        decelerationRandom();
        // brake
    }
    speedVariation(x);
    changeDistance(duration);
}

//for the bots to change parts each lap
void Car::autoChangeParts() {
    Car::fuel = 100;
    Car::brakeWear = 0;
    Car::tyreWear = 0;
    Car::engineWear = 0;
    Car::tyrePressure = 21.5;
}

//displays the telemetries of the user's car in a simple way
void Car::displayTelemetries(int pos) {
    cout << name << ":" << endl;
    cout << "lap: " << lap << ", position: " << pos%50 << endl;
    cout <<"fuel: " << fuel << "L" << ", speed: " << speed << endl;
    cout <<"engineWear: " << engineWear << "%" << ", engineTemp: " << engineTemp << "C" << ", turbo pressure: " << turboPressure << endl;
    cout <<"brakeWear: " << brakeWear << "%" << ", brakeTemp: " << brakeTemp << "C" << endl;
    cout << "Tyre Wear: " << tyreWear << "%" << ", Tyre pressure: " << tyrePressure << "psi" << endl;
    cout << "ABS status: " << antiLockBS << ", DRS status: " << DRS << endl;
}

//tells the user to fix some things with his cars
void Car::userChangeParts() {
    float refuel;
    bool goodRefuel = false;
    string changeWheels;
    string changeBrakes;
    string changeEngine;
    string antilockBSOn;
    string DRSOnOff;

    while (!goodRefuel) {
        cout << "How much fuel do you want to put in " << name << "'s " << "car?" << endl;
        //please, for the sake of god, don't input a string for the fuel amount xD
        try {
            cin >> refuel;
            cout << endl;
        } catch (int e) {
            cout << "You didn't input a valid number! Try again!" << endl;
            continue;
        }

        if (refuel < 0) {
            cout << "You didn't input a valid number! Try again!" << endl;
            continue;
        }else if ((fuel + refuel) > 150) {
            cout << "Fuel amount is too high! Defaulting to 150L." << endl;
            fuel = 150;
            goodRefuel = true;
        } else {
            cout << "Refuel successful!" << endl;
            fuel += refuel;
            goodRefuel = true;
        }
    }

    cout << "Do you want to change " << name << "'s " << "tyres? (Y/n)" << endl;
    cin >> changeWheels;
    cout << endl;
    if (changeWheels == "Y" || changeWheels == "y" || changeWheels == "Yes" || changeWheels == "yes") {
        cout << "Change tyres successful!" << endl;
        Car::tyrePressure = 21.5;
        Car::tyreWear = 0;
    }

    cout << "Do you want to repair " << name << "'s " << "brakes? (Y/n)" << endl;
    cin >> changeBrakes;
    cout << endl;
    if (changeBrakes == "Y" || changeBrakes == "y" || changeBrakes == "Yes" || changeBrakes == "yes") {
        cout << "Repair brakes successful!" << endl;
        Car::brakeWear = 0;
    }

    cout << "Do you want to repair " << name << "'s " << "engine? (Y/n)" << endl;
    cin >> changeEngine;
    cout << endl;
    if (changeBrakes == "Y" || changeBrakes == "y" || changeBrakes == "Yes" || changeBrakes == "yes") {
        cout << "Repair engine successful!" << endl;
        Car::engineWear = 0;
    }

    cout << "Do you want to turn " << name << "'s " << "DRS on? (Y/n)" << endl;
    cin >> DRSOnOff;
    cout << endl;
    if (DRSOnOff == "Y" || DRSOnOff == "y" || DRSOnOff == "Yes" || DRSOnOff == "yes") {
        cout << "DRS turned on!" << endl;
        DRS = true;
    }else {
        cout << "DRS turned off!" << endl;
        DRS = false;
    }

    cout << "Do you want to turn " << name << "'s " << "ABS on? (Y/n)" << endl;
    cin >> antilockBSOn;
    cout << endl;
    if (antilockBSOn == "Y" || antilockBSOn == "y" || antilockBSOn == "Yes" || antilockBSOn == "yes") {
        cout << "HAHA LOL YOU CAN'T DO THAT!" << endl;
        this_thread::sleep_for(1s);
    }
}

//see if the car is still running
bool Car::isCarActive() const {
    return carActive;
}

//just to see the status (breakdown, crash or finished)
string Car::getStatus() {
    return status;
}

//for the dislay of the ranking at the end
int Car::getRank() {
    return rank;
}

//when a car finishes the number of laps it has to do
//prompt that it has finished the race
//assign a rank
void Car::setFinished(string fin, int rank) {
    cout << name << " has finished the race!" << endl;
    Car::rank = rank;
    carActive = false;
    Car::status = fin;
}

//the conditions to see if the car is on breakdown or not
void Car::breakDown() {
    if (fuel <= 0 || antiLockBS || engineWear >= 50 || tyreWear >= 50 || tyrePressure < 18) {
        carActive = false;
        status = "breakdown";
    }
}

//poor car... it went in a wall :'(
void Car::checkCrash(int x) {
    if ((x == 1 && speed > 180) || (x == 0 && speed > 140)) {  // sharp corner or u-turn with too much speed
        carActive = false;
        status = "crash";
    }
}











