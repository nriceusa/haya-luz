#include <fstream>
#include <iostream>

#include "Image/Image.h"
#include "Scene.h"
#include "Utilities/FileManager.h"

int main(int argc, char* argv[]) {
    Scene scene;
    if (argc == 2) {
        std::ifstream inputFile(argv[1]);
        if (!inputFile) {
            std::cerr << "Error: Could not open input file: " << argv[1] << std::endl;
            return 1;
        }
        FileManager::readSceneFromFile(inputFile, scene);
    } else {
        std::cerr << "Error: Incorrect number of arguments. Please provide one scene file." << std::endl;
        return 1;
    }

    std::ofstream& outputFile = FileManager::openFile();

    const size_t image_width = 512;  // TODO: Allow user to specify image width and height.
    const size_t image_height = 512;
    Image image(image_width, image_height);

    FileManager::saveImageToFile(image, outputFile);

    std::cout << "haya-luz exited successfully." << std::endl;
    return 0;
}
