#ifndef HAYA_LUZ_PIXEL_H
#define HAYA_LUZ_PIXEL_H

#include "Color.h"

class Pixel {
private:
    Color color;

public:
    Pixel() : color(Color(0, 0, 0)) {}
    Pixel(const Color& color) : color(color) {}
    
    double getR() const {
        return color.getR();
    }

    double getG() const {
        return color.getG();
    }

    double getB() const {
        return color.getB();
    }

    void setR(const double newR) {
        color.setR(newR);
    }

    void setG(const double newG) {
        color.setG(newG);
    }

    void setB(const double newB) {
        color.setB(newB);
    }

    void setRGB(const double newR, const double newG, const double newB) {
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
