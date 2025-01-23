#include <fstream>
#include <iostream>

#include "Image/Image.h"

int main() {
    // Open file
    std::string outputFileName;
    std:: cout << "Enter output file name:";
    std::cin >> outputFileName;
    outputFileName += ".ppm";

    std::ofstream outputFile;
    outputFile.open(outputFileName);

    const size_t image_width = 512;
    const size_t image_height = 512;
    Image image(image_width, image_height);
    
    // Write file
    outputFile << "P3" << std::endl;  // ASCII file
    outputFile << screen.getWidth() << " " << screen.getHeight() << std::endl;  // Number of columns and rows
    outputFile << "255" << std::endl;  // Maximum color value
    outputFile << screen << std::endl;  // Pixel values

    return 0;
}