#include <fstream>
#include <iostream>

#include "Image/Image.h"
#include "Renderer/RayTracer.h"
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

    std::cout << scene << std::endl;
    scene.alignToActiveCamera();

    std::ofstream& outputFile = FileManager::openOutputFile();

    const uint image_width = 128;  // TODO: Allow user to specify image width and height.
    const uint image_height = 128;
    Image image(image_width, image_height);

    RayTracer rayTracer;
    rayTracer.render(scene, image);

    FileManager::saveImageAsPPM(image, outputFile);

    std::cout << "haya-luz exited successfully." << std::endl;
    return 0;
}
