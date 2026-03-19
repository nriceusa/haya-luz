#ifndef HAYA_LUZ_IMAGE_H
#define HAYA_LUZ_IMAGE_H

#define DEFAULT_WIDTH 64
#define DEFAULT_HEIGHT 36

#include <vector>

#include "Color.h"
#include "Pixel.h"
#include "../Utilities/Vector3.h"

class Image {
private:
    std::vector<std::vector<Pixel>> pixels;
    std::string path;

public:
    Image() : Image(DEFAULT_WIDTH, DEFAULT_HEIGHT, "") {}

    Image(const uint width, const uint height) : Image(width, height, "") {}

    Image(const uint width, const uint height, const std::string& path) :
        pixels(width, std::vector<Pixel>(height)), path(path) {}
    

    uint getWidth() const {
        return pixels.size();
    }

    uint getHeight() const {
        return pixels[0].size();
    }

    const Pixel& getPixel(const uint x, const uint y) const {
        return pixels[x][y];
    }

    void setPixelColor(const uint x, const uint y, const Color& color) {
        pixels[x][y].setRGB(color.getR(), color.getG(), color.getB());
    }

    void setPixelColor(const uint x, const uint y, const double r, const double g, const double b) {
        pixels[x][y].setRGB(r, g, b);
    }

    friend std::ostream& operator<<(std::ostream& os, const Image& image) {
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
