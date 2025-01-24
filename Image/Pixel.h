#ifndef HAYA_LUZ_PIXEL_H
#define HAYA_LUZ_PIXEL_H

#include "../Utilities/Vector3.h"

class Pixel {
private:
    Vector3 color;

public:
    Pixel() : color(Vector3(0, 0, 0)) {}
    Pixel(const Vector3& color) : color(color) {}
    
    double getR() const {
        return color.getR();
    }

    double getG() const {
        return color.getG();
    }

    double getB() const {
        return color.getB();
    }

    void setR(double newR) {
        color.setR(newR);
    }

    void setG(double newG) {
        color.setG(newG);
    }

    void setB(double newB) {
        color.setB(newB);
    }

    void setRGB(double newR, double newG, double newB) {
        color.setR(newR);
        color.setG(newG);
        color.setB(newB);
    }

    friend std::ostream &operator<<(std::ostream& os, const Pixel& pixel) {
        os << std::to_string(pixel.getR()) << ' ' << std::to_string(pixel.getG()) << ' ' << std::to_string(pixel.getB());
        return os;
    }
};

#endif //HAYA_LUZ_PIXEL_H
