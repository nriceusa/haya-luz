#ifndef HAYA_LUZ_IMAGE_H
#define HAYA_LUZ_IMAGE_H

#define DEFAULT_WIDTH 100
#define DEFAULT_HEIGHT 75

#include <vector>

#include "Pixel.h"

class Image {
private:
    std::vector<std::vector<Pixel>> pixels;

public:
    Image() : pixels(DEFAULT_WIDTH, std::vector<Pixel>(DEFAULT_HEIGHT)) {}
    Image(const uint width, const uint height) : pixels(width, std::vector<Pixel>(height)) {}

    uint getWidth() const {
        return pixels.size();
    }

    uint getHeight() const {
        return pixels[0].size();
    }

    const Pixel& getPixel(const uint x, const uint y) const {
        return pixels[x][y];
    }

    void setPixelRGB(const uint x, const uint y, const double r, const double g, const double b) {
        pixels[x][y].setRGB(r, g, b);
    }

    friend std::ostream &operator<<(std::ostream& os, const Image& image) {
        for (uint y = 0; y < image.getHeight(); ++y) {
            for (uint x = 0; x < image.getWidth(); ++x) {
                os << image.getPixel(x, y) << "  ";
            }
            os << std::endl;
        }
        return os;
    }
};

#endif //HAYA_LUZ_IMAGE_H
