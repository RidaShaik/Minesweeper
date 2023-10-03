#pragma once

#include <string>
#include <iomanip>
#include <random>
#include <ctime>
using namespace std;



class Random {

    static mt19937 random;

public:
    static int IntRan(int min, int max);
    static float FloRan(float min, float max);
};