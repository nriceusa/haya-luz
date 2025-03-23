#ifndef HAYA_LUZ_UTILITIES_H
#define HAYA_LUZ_UTILITIES_H

#include <cmath>
#include <algorithm>

class Utilities {
public:
    Utilities() = delete;

    static double degreesToRadians(const double valInDegrees) {
        return valInDegrees * (M_PI / 180);
    }

    static double radiansToDegrees(const double valInRadians) {
        return valInRadians * (180 / M_PI);
    }

    static uint doubleTo256(const double value) {
        return static_cast<uint>(
            std::max(0.0, std::min(value * 255, 255.0))
        );
    }

    static double clamp(const double value, const double min, const double max) {
        return std::max(min, std::min(value, max));
    }
};

#endif //HAYA_LUZ_UTILITIES_H