#ifndef HAYA_LUZ_COLOR_H
#define HAYA_LUZ_COLOR_H

#include <iostream>

// TODO: Is this class a redundancy of the Pixel class? (Maybe not, if we implement texture maps.)

class Color {
private:
    double r;
    double g;
    double b;
    double alpha;

public:
    Color() : r(0), g(0), b(0), alpha(1) {}

    Color(const double r, const double g, const double b) : r(r), g(g), b(b), alpha(1) {}

    Color(const double r, const double g, const double b, const double alpha) : r(r), g(g), b(b), alpha(alpha) {}

    double getR() const {
        return r;
    }

    double getG() const {
        return g;
    }

    double getB() const {
        return b;
    }

    double getAlpha() const {
        return alpha;
    }

    void setR(const double newR) {
        r = newR;
    }

    void setG(const double newG) {
        g = newG;
    }

    void setB(const double newB) {
        b = newB;
    }

    void setAlpha(const double newAlpha) {
        alpha = newAlpha;
    }

    void setRGB(const double newR, const double newG, const double newB) {
        r = newR;
        g = newG;
        b = newB;
    }

    void setRGBA(const double newR, const double newG, const double newB, const double newAlpha) {
        r = newR;
        g = newG;
        b = newB;
        alpha = newAlpha;
    }

    friend Color operator+(const Color &colorLeft, const Color &colorRight) {
        return Color{colorLeft.getR() + colorRight.getR(),
                     colorLeft.getG() + colorRight.getG(),
                     colorLeft.getB() + colorRight.getB()};
    }

    friend Color operator-(const Color &colorLeft, const Color &colorRight) {
        return Color{colorLeft.getR() - colorRight.getR(),
                     colorLeft.getG() - colorRight.getG(),
                     colorLeft.getB() - colorRight.getB()};
    }

    friend Color operator*(const Color &colorLeft, const Color &colorRight) {
        return Color{colorLeft.getR() * colorRight.getR(),
                     colorLeft.getG() * colorRight.getG(),
                     colorLeft.getB() * colorRight.getB()};
    }

    friend Color operator*(const double factor, const Color &color) {
        return Color{factor * color.getR(),
                     factor * color.getG(),
                     factor * color.getB()};
    }

    friend Color operator*(const Color &color, const double factor) {
        return factor * color;
    }

    friend Color operator/(const Color &color, const double dividend) {
        return 1 / dividend * color;
    }

    friend std::ostream &operator<<(std::ostream &os, const Color &color) {
        os << color.getR() << " " << color.getG() << " " << color.getB() << " " << color.getAlpha();
        return os;
    }
};

#endif //HAYA_LUZ_COLOR_H