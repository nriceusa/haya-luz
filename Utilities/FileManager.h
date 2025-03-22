#ifndef HAYA_LUZ_FILEMANAGER_H
#define HAYA_LUZ_FILEMANAGER_H

#include "../Image/Image.h"
#include "../Image/Pixel.h"
#include "../Scene.h"
#include "../SceneComponents/Camera.h"
#include "../SceneComponents/Geometry/Material.h"
#include "../SceneComponents/Geometry/Polygon.h"
#include "../SceneComponents/Geometry/Sphere.h"
#include "../SceneComponents/Geometry/Triangle.h"
#include "../SceneComponents/Lights/DirectionalLight.h"
#include "../SceneComponents/Sky.h"
#include "Utilities.h"

#include <fstream>
#include <iostream>
#include <sstream>

class FileManager {
private:
    static uint readUint(std::istringstream& lineStream) {
        uint value;
        lineStream >> value;
        return value;
    }

    static double readDouble(std::istringstream& lineStream) {
        double value;
        lineStream >> value;
        return value;
    }

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
                const Vector3 intensity = readVector3(lineStream);
                const double intensityScalar = readDouble(lineStream);

                scene.setSky(Sky(intensityScalar, intensity));

            } else if (type == "CAMERA") {
                const Vector3 origin = readVector3(lineStream);
                const Vector3 target = readVector3(lineStream);
                const double fieldOfView = readDouble(lineStream);

                scene.addCamera(Camera(fieldOfView, origin, target));

            } else if (type == "DIRECTIONAL_LIGHT") {
                const Vector3 direction = readVector3(lineStream);
                const Vector3 intensity = readVector3(lineStream);
                const double intensityScalar = readDouble(lineStream);

                scene.addLight(DirectionalLight(intensityScalar, intensity, direction));
                
            } else if (type == "POINT_LIGHT") {
                const Vector3 location = readVector3(lineStream);
                const Vector3 intensity = readVector3(lineStream);
                const double intensityScalar = readDouble(lineStream);

                scene.addLight(PointLight(intensityScalar, intensity, location));

            } else if (type == "MATERIAL") {
                const uint id = readUint(lineStream);

                const Vector3 diffuseIntensity = readVector3(lineStream);
                const Vector3 specularIntensity = readVector3(lineStream);
                const Vector3 emissionIntensity = readVector3(lineStream);
                const double diffuse = readDouble(lineStream);
                const double specular = readDouble(lineStream);
                const double specularRoughness = readDouble(lineStream);
                const double emissivity = readDouble(lineStream);

                Material material(diffuseIntensity, specularIntensity, emissionIntensity, diffuse,
                                  specular, specularRoughness, emissivity);
                scene.addMaterial(material);

                std::cout << ">>Material: " << material << std::endl;

            } else if (type == "SPHERE") {
                const uint materialId = readUint(lineStream);
                const Vector3 center = readVector3(lineStream);
                const double radius = readDouble(lineStream);

                Sphere sphere(scene.getMaterial(materialId), center, radius);
                scene.addGeometry(sphere);
                
            } else if (type == "TRIANGLE") {
                const uint materialId = readUint(lineStream);
                const Vector3 point1 = readVector3(lineStream);
                const Vector3 point2 = readVector3(lineStream);
                const Vector3 point3 = readVector3(lineStream);

                Triangle triangle(scene.getMaterial(materialId), point1, point2, point3);
                scene.addGeometry(triangle);

            } else if (type == "POLYGON") {
                const uint materialId = readUint(lineStream);
                const uint numVertices = readUint(lineStream);
                std::vector<Vector3> points;
                for (uint i = 0; i < numVertices; ++i) {
                    points.push_back(readVector3(lineStream));
                }

                Polygon polygon(scene.getMaterial(materialId), points);
                scene.addGeometry(polygon);

            } else if (type == "" || type == "#") {
                // Do nothing
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

    static std::ofstream& openOutputFile() {
        std::cout << "Would you like to enter a name for the output file? (y/n): ";
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

    static void saveImageAsPPM(const Image& image, std::ofstream& file) {
        // Header
        file << "P3" << std::endl;  // ASCII file
        file << image.getWidth() << " " << image.getHeight() << std::endl;  // Number of columns and rows
        file << "255" << std::endl;  // Maximum color value

        // Convert pixel values to char and write to file
        for (uint y = 0; y < image.getHeight(); ++y) {
            for (uint x = 0; x < image.getWidth(); ++x) {
                const Pixel& pixel = image.getPixel(x, y);
                file << Utilities::doubleTo256(pixel.getR()) << " "
                     << Utilities::doubleTo256(pixel.getG()) << " "
                     << Utilities::doubleTo256(pixel.getB()) << "  ";
            }
            file << std::endl;
        }
    }
};

#endif //HAYA_LUZ_FILEMANAGER_H