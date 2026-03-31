#ifndef HAYA_LUZ_IMAGE_H
#define HAYA_LUZ_IMAGE_H

#define DEFAULT_WIDTH 64
#define DEFAULT_HEIGHT 36

#include "stb_image.h"

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
        pixels(width, std::vector<Pixel>(height)), path(path)
    {
        if (!path.empty()) {
            int width, height, numChannels;
            unsigned char* data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);

            if (data == nullptr) {
                std::cerr << "Error: Failed to load image from path: " << path << std::endl;
            }

            for (uint y = 0; y < height; ++y) {
                for (uint x = 0; x < width; ++x) {
                    const int index = (y * width + x) * numChannels;
                    const double r = data[index] / 255.0;
                    const double g = data[index + 1] / 255.0;
                    const double b = data[index + 2] / 255.0;
                    pixels[x][y].setRGB(r, g, b);
                }
            }

            stbi_image_free(data);
        }
    }
    
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

    const Vector3 sample(const double u, const double v) const {
        const double x = u * (this->getWidth() - 1);
        const double y = v * (this->getHeight() - 1);
        
        const uint xLeft = static_cast<uint>(floor(x));
        const uint xRight = static_cast<uint>(ceil(x));
        const uint yTop = static_cast<uint>(floor(y));
        const uint yBottom = static_cast<uint>(ceil(y));

        const Vector3& topLeftColor = pixels[xLeft][yTop].getRGB();
        const Vector3& topRightColor = pixels[xRight][yTop].getRGB();
        const Vector3& bottomLeftColor = pixels[xLeft][yBottom].getRGB();
        const Vector3& bottomRightColor = pixels[xRight][yBottom].getRGB();

        const double xWeight = x - xLeft;
        const double yWeight = y - yTop;
        const Vector3 topColor = (1 - xWeight) * topLeftColor + xWeight * topRightColor;
        const Vector3 bottomColor = (1 - xWeight) * bottomLeftColor + xWeight * bottomRightColor;
        return (1 - yWeight) * topColor + yWeight * bottomColor;
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
