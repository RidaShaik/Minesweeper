#include <string>
#include <iomanip>
#include <random>
#include <ctime>
using namespace std;
#include "Random.h"



mt19937 Random::random(time(0));

int Random::IntRan(int min, int max) {
    uniform_int_distribution<int> dist(min, max);
    return dist(random);
}

float Random::FloRan(float min, float max) {
    uniform_real_distribution<float> dist(min, max);
    return dist(random);
}