#ifndef HAYA_LUZ_UTILITIES_H
#define HAYA_LUZ_UTILITIES_H

#include <cmath>

class Utilities {
public:
    Utilities() = delete;

    static double degreesToRadians(const double valInDegrees) {
        return valInDegrees * (M_PI / 180);
    }

    static double radiansToDegrees(const double valInRadians) {
        return valInRadians * (180 / M_PI);
    }

    static uint convertTo256(const double value) {
        return static_cast<uint>(value * 255);
    }
};

#endif //HAYA_LUZ_UTILITIES_H