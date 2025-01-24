#include <fstream>
#include <iostream>

#include "Image/Image.h"
#include "Utilities/FileManager.h"

int main() {
    std::ofstream& outputFile = FileManager::openFile();

    const size_t image_width = 512;
    const size_t image_height = 512;
    Image image(image_width, image_height);

    FileManager::saveImageToFile(image, outputFile);

    std::cout << "haya-luz exited successfully." << std::endl;
    return 0;
}
