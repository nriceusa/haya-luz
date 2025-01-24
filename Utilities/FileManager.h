#ifndef HAYA_LUZ_FILEMANAGER_H
#define HAYA_LUZ_FILEMANAGER_H

#include "../Image/Image.h"
#include "../Image/Pixel.h"

#include <fstream>
#include <iostream>

class FileManager {
private:
    static unsigned char convertToChar(const double& value) {
        return static_cast<unsigned char>(value * 255);
    }

public:
    FileManager() = delete;

    static std::ofstream& openFile(const std::string& fileName) {
        static std::ofstream file;
        file.open("Renders/" + fileName + ".ppm");
        return file;
    }

    static std::ofstream& openFile() {
        std::cout << "Would you like to enter a file name? (y/n): ";
        char response = std::cin.get();
        
        if (response == 'y' || response == 'Y') {
            static std::string fileName;
            std::cout << "Enter output file name: ";
            std::cin >> fileName;
            return openFile(fileName);
        }

        std::cout << "Using default file name: test" << std::endl;
        return openFile("test");
    }

    static void saveImageToFile(const Image& image, std::ofstream& file) {
        // Header
        file << "P3" << std::endl;  // ASCII file
        file << image.getWidth() << " " << image.getHeight() << std::endl;  // Number of columns and rows
        file << "255" << std::endl;  // Maximum color value

        // Convert pixel values to char and write to file
        for (size_t y = 0; y < image.getHeight(); ++y) {
            for (size_t x = 0; x < image.getWidth(); ++x) {
                const Pixel& pixel = image.getPixel(x, y);
                file << convertToChar(pixel.getR()) << " " << convertToChar(pixel.getG()) << " " << convertToChar(pixel.getB()) << "  ";
            }
            file << std::endl;
        }

        file << image << std::endl;  // Pixel values
    }
};

#endif //HAYA_LUZ_FILEMANAGER_H