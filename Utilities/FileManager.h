#ifndef HAYA_LUZ_FILEMANAGER_H
#define HAYA_LUZ_FILEMANAGER_H

#include "Image/Image.h"

#include <fstream>
#include <iostream>

class FileManager {
private:
    static unsigned char convertToChar(const double& value) {
        return static_cast<unsigned char>(value * 255);
    }

public:
    FileManager() : {}

    static const std::ofstream& openFile(const std::string& fileName) {
        std::ofstream file;
        file.open(fileName + ".ppm");
        return file;
    }

    static const std::ofstream& openFile() {
        std::string fileName;
        std::cout << "Enter output file name:";
        std::cin >> fileName;
        return openFile(fileName);
    }

    static void saveImageToFile(const Image& image, const std::ofstream& file) {
        file << "P3" << std::endl;  // ASCII file
        file << image.getWidth() << " " << image.getHeight() << std::endl;  // Number of columns and rows
        file << "255" << std::endl;  // Maximum color value
        file << image << std::endl;  // Pixel values
    }
}

#endif //HAYA_LUZ_FILEMANAGER_H