#ifndef HAYA_LUZ_RAYTRACER_H
#define HAYA_LUZ_RAYTRACER_H

#define MIN_CLIPPING_DISTANCE 0.001

#include <iostream>
#include <future>
#include <vector>
#include <atomic>
#include <mutex>

#include "../Image/Image.h"
#include "Ray.h"
#include "../Scene.h"

class Renderer {
private:
    const uint numGlossyBounces;
    const uint numPixelSamples;
    const double minClippingDistance;
    const double maxClippingDistance;

public:
    Renderer() : Renderer(3, 4) {}

    Renderer(const uint numGlossyBounces, const uint numPixelSamples) :
        Renderer(
            numGlossyBounces,
            numPixelSamples,
            MIN_CLIPPING_DISTANCE,
            std::numeric_limits<double>::max()
        ) {}

    Renderer(
        const uint numGlossyBounces,
        const uint numPixelSamples,
        double minClippingDistance,
        double maxClippingDistance
    ) :
        numGlossyBounces(numGlossyBounces),
        numPixelSamples(numPixelSamples),
        minClippingDistance(std::max(minClippingDistance, MIN_CLIPPING_DISTANCE)),
        maxClippingDistance(maxClippingDistance) {}
    

    void render(Scene& scene, Image& image) const {
        const Camera& camera = scene.getActiveCamera();
        const Vector3 baseRayVector = Vector3::normalize(camera.getRotation());

        const double xOffset = baseRayVector.getZ() * tan(camera.getFieldOfView() / 2);
        const double yOffset = -xOffset * (static_cast<double>(image.getHeight()) / static_cast<double>(image.getWidth()));
        const double pixelWidth = (2 * -xOffset) / static_cast<double>(image.getWidth());
        const double sampleWidth = pixelWidth / static_cast<double>(numPixelSamples);
        
        const double initialX = baseRayVector.getX() + xOffset + (sampleWidth / 2);
        const double initialY = baseRayVector.getY() + yOffset + (sampleWidth / 2);

        // Precompute bounding volume to avoid doing it in parallel threads
        std::cout << "Building BVH..." << std::endl;
        scene.getBoundingVolume();

        const uint progressBarSpace = 50;
        std::atomic<uint> completedColumns(0);
        std::mutex consoleMutex;
        std::vector<std::future<void>> futures;

        std::cout << "Rendering pixels..." << std::endl;
        std::cout << "[";
        for (uint i = 0; i < progressBarSpace; ++i) {
            std::cout << " ";
        }
        std::cout << "] 0 %\r";
        std::cout.flush();

        for (uint x = 0; x < image.getWidth(); ++x) {
            futures.push_back(std::async(std::launch::async, [=, &scene, &image, &completedColumns, &consoleMutex]() {

                for (uint y = 0; y < image.getHeight(); ++y) {
                    Vector3 pixelColor(0, 0, 0);

                    for (uint sampleX = 0; sampleX < numPixelSamples; ++sampleX) {
                        for (uint sampleY = 0; sampleY < numPixelSamples; ++sampleY) {
                            Vector3 rayVector = baseRayVector;
                            rayVector.setX(initialX + (x * pixelWidth) + (sampleX * sampleWidth));
                            rayVector.setY(initialY - (y * pixelWidth) - ((sampleY + 1) * sampleWidth));

                            Vector3 jitteredRay = Vector3::jitter(rayVector, sampleWidth / 2);

                            const Ray ray(camera.getOrigin(), jitteredRay, scene, minClippingDistance, maxClippingDistance);
                            pixelColor += ray.trace(numGlossyBounces);
                        }
                    }

                    pixelColor /= static_cast<double>(numPixelSamples * numPixelSamples);
                    pixelColor.setR(Utilities::clamp(pixelColor.getR(), 0, 1));
                    pixelColor.setG(Utilities::clamp(pixelColor.getG(), 0, 1));
                    pixelColor.setB(Utilities::clamp(pixelColor.getB(), 0, 1));
                    image.setPixelColor(x, y, pixelColor.getR(), pixelColor.getG(), pixelColor.getB());
                }

                const uint completed = ++completedColumns;
                const double progress = static_cast<double>(completed) / static_cast<double>(image.getWidth());
                const uint progressBarWidth = static_cast<uint>(progressBarSpace * progress);
                
                std::lock_guard<std::mutex> lock(consoleMutex);
                std::cout << "[";
                for (uint i = 0; i < progressBarSpace; ++i) {
                    if (i < progressBarWidth) {
                        std::cout << "=";
                    } else if (i == progressBarWidth) {
                        std::cout << ">";
                    } else {
                        std::cout << " ";
                    }
                }
                std::cout << "] " << uint(progress * 100.0) << " %\r";
                std::cout.flush();
            }));
        }

        for (std::future<void>& future : futures) {
            future.get();
        }

        std::cout << "[";
        for (uint i = 0; i < progressBarSpace; ++i) {
            std::cout << "=";
        }
        std::cout << "] 100 %" << std::endl;
    }
};

#endif //HAYA_LUZ_RAYTRACER_H
