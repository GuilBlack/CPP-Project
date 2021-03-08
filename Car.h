//
// Created by guill on O4/O5/2O2O.
//
#include <string>
#include <chrono>
#include <iostream>
#include <thread>
#ifndef FINAL_PROJECT_CAR_H
#define FINAL_PROJECT_CAR_H

using namespace std;

//we tried to do a class tyre, brake and engine and do a composition with this class but we had some error
//that we couldn't figure out how to correct so we did all in 1 class :/

class Car {
private:
    static const int MAX_ACCELERATION = 45;
    static const int MAX_DECELERATION = 60;
    constexpr const static float TURBO_PRESSURE_MAX = 3.5;
    float maxSpeed = 323;
    float fuel;
    int lap = 1;
    double distance = 0;
    float speed = 0;
    double speedMS;
    string name;
    string status = "";
    int rank = 0;
    bool DRS = false;
    bool antiLockBS;

    int coord[2] = {3, 4};
    bool checkPos = false;

    int calculatedMaxDec = 40;

    float accCoef;
    float decCoef;
    float engineTemp = 0;
    float engineWear = 0;
    float turboPressure = 0;
    int acceleration = 0;
    int deceleration = 0;

    float tyrePressure = 21.5;
    float tyreWear = 0;

    float brakeTemp;
    float brakeWear = 0;

    bool carActive = true;


private:

    void calculateFuel();

    void calculateBrakeCoef();
    void calculateBrakeWear();
    void calculateBrakeStats();
    void calculateTyreWear();
    void calculateTyreWearInBrake();
    void calculateTyrePressure();

    void calculateAccCoef();
    void calculateTurboPressure();
    void calculateEngineStats();

    void accelerationRandom();
    void decelerationRandom();
    void speedVariation(int x);
    void changeDistance(double duration);

public:
    void setCheckPos(bool checkPos);
    bool isCheckPos() const;
    bool isCarActive() const;
    void setFinished(string fin, int rank);
    int getRank();

    Car(float = 100, string = randomName(), int = 0);
    const string getName() const;
    static string randomName();
    void autoChangeParts();

    int getCoordX();
    int getCoordY();
    int getLap();
    double getDistance() const;
    string getStatus();

    void setCoord(int x, int y);
    void brakeOrAccelerate(int x, double duration);
    void setDistance(double distance);
    float getFuel() const;
    void increaseLap();
    void displayTelemetries(int pos);
    void userChangeParts();
    void breakDown();
    void checkCrash(int x);

};


#endif //FINAL_PROJECT_CAR_H
