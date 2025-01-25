#ifndef HAYA_LUZ_FILEMANAGER_H
#define HAYA_LUZ_FILEMANAGER_H

#include "../Image/Image.h"
#include "../Image/Pixel.h"
#include "../Scene.h"
#include "../Utilities/Utilities.h"

#include <fstream>
#include <iostream>
#include <sstream>

class FileManager {
private:
    static Vector3 readVector3(std::istringstream& lineStream) {
        double x, y, z;
        lineStream >> x >> y >> z;
        return Vector3(x, y, z);
    }

public:
    FileManager() = delete;

    static Scene& readSceneFromFile(std::ifstream& file, Scene& scene) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            std::string type;
            lineStream >> type;

            if (type == "SKY") {
                
            } else if (type == "CAMERA") {
                
            } else if (type == "DIRECTIONAL_LIGHT") {
                
            } else if (type == "POINT_LIGHT") {

            } else if (type == "MATERIAL") {
                
            } else if (type == "SPHERE") {
                
            } else if (type == "TRIANGLE") {
                
            } else {
                std::cerr << "Error: Unknown type from input file: " << type << std::endl;
            }
        }

        return scene;
    }

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
                file << Utilities::convertToChar(pixel.getR()) << " "
                     << Utilities::convertToChar(pixel.getG()) << " "
                     << Utilities::convertToChar(pixel.getB()) << "  ";
            }
            file << std::endl;
        }

        file << image << std::endl;  // Pixel values
    }
};

#endif //HAYA_LUZ_FILEMANAGER_H