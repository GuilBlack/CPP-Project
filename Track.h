//
// Created by guill on 04/05/2020.
//
#include <iostream>
#include <chrono>
#include <ctime>
#include "time.h"
#include "Car.h"
#include <string>
#include <thread>

using namespace std;
using namespace chrono;


#ifndef FINAL_PROJECT_TRACK_H
#define FINAL_PROJECT_TRACK_H


class Track {
private:
    static int const ROAD_COORD = 50;
    static int const COORD_XY = 2;
    static int const NUM_CARS = 22;
    int laps;
    int rank = 1;
    Car cars[NUM_CARS];

public:
    constexpr static int circuit[ROAD_COORD][COORD_XY] = {{3, 4}, {3, 5}, {3, 6}, {3, 7}, {2, 7}, {1, 7}, {0, 8}, {1, 9}, {2, 9}, {3, 9},
                                                      {4, 9}, {5, 9}, {6, 9}, {7, 9}, {8, 9}, {8, 10}, {8, 11}, {8, 12}, {8, 13}, {9, 14},
                                                      {10, 13}, {10, 12}, {10, 11}, {10, 10}, {10, 9}, {10, 8}, {10, 7}, {10, 6}, {9, 6}, {8, 6},
                                                      {7, 6}, {6, 5}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 3}, {11, 2}, {10, 2},
                                                      {9, 2}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {5, 1}, {4, 0}, {3, 1}, {3, 2}, {3, 3}};


    // Indexes of all corner coordinates
    constexpr static int allCorners[9] = {6, 3, 19, 14, 31, 27, 37, 44, 46};

    constexpr static int pitStop[COORD_XY] = {2, 4};

    void printCircuit();
    void initCars();
    void printRaceState();
    void finish();
    void numberOfLaps();
    void run();

};


#endif //FINAL_PROJECT_TRACK_H
