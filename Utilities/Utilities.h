#ifndef HAYA_LUZ_UTILITIES_H
#define HAYA_LUZ_UTILITIES_H

#include <cmath>

class Utilities {
public:
    Utilities() = delete;

    static double degreesToRadians(const double valInDegrees) {
        return valInDegrees * (M_PI / 180);
    }

    static unsigned char convertToChar(const double value) {
        return static_cast<unsigned char>(value * 255);
    }
};

#endif //HAYA_LUZ_UTILITIES_H