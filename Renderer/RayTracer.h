#ifndef HAYA_LUZ_RAYTRACER_H
#define HAYA_LUZ_RAYTRACER_H

#define MIN_CLIPPING_DISTANCE 0.001

#include "../Image/Image.h"
#include "Ray.h"
#include "../Scene.h"

class RayTracer {
private:
    const uint numGlossyBounces;
    const uint numPixelSamples;
    const double minClippingDistance;
    const double maxClippingDistance;

public:
    RayTracer() :
        numGlossyBounces(4),
        numPixelSamples(1),
        minClippingDistance(MIN_CLIPPING_DISTANCE),
        maxClippingDistance(std::numeric_limits<double>::max()) {}

    RayTracer(const uint numGlossyBounces, const uint numPixelSamples) :
        numGlossyBounces(numGlossyBounces),
        numPixelSamples(numPixelSamples),
        minClippingDistance(MIN_CLIPPING_DISTANCE),
        maxClippingDistance(std::numeric_limits<double>::max()) {}

    RayTracer(const uint numGlossyBounces, const uint numPixelSamples, double minClippingDistance, double maxClippingDistance) :
        numGlossyBounces(numGlossyBounces),
        numPixelSamples(numPixelSamples),
        minClippingDistance(std::max(minClippingDistance, MIN_CLIPPING_DISTANCE)),
        maxClippingDistance(maxClippingDistance) {}

    void render(const Scene& scene, Image& image) const {
        const Camera& camera = scene.getActiveCamera();
        Vector3 rayVector = Vector3::normalize(camera.getRotation());

        const double xOffset = rayVector.getZ() * tan(camera.getFieldOfView() / 2);
        const double yOffset = -xOffset * (static_cast<double>(image.getHeight()) / static_cast<double>(image.getWidth()));
        const double pixelWidth = (2 * -xOffset) / static_cast<double>(image.getWidth());
        const double sampleWidth = pixelWidth / static_cast<double>(numPixelSamples);
        const double initialX = rayVector.getX() + xOffset + (sampleWidth / 2);
        const double initialY = rayVector.getY() + yOffset + (sampleWidth / 2);

        rayVector.setX(initialX);
        rayVector.setY(initialY);
        for (uint x = 0; x < image.getWidth(); ++x) {
            for (uint y = 0; y < image.getHeight(); ++y) {
                Vector3 pixelColor(0, 0, 0);
                for (uint sampleX = 0; sampleX < numPixelSamples; ++sampleX) {
                    for (uint sampleY = 0; sampleY < numPixelSamples; ++sampleY) {
                        rayVector.setY(rayVector.getY() - sampleWidth);
                        Vector3 jitteredRay = Vector3::jitter(rayVector, sampleWidth / 2);

                        const Ray ray(camera.getOrigin(), jitteredRay, scene, minClippingDistance, maxClippingDistance);
                        pixelColor += ray.trace(numGlossyBounces);
                    }
                    rayVector.setX(rayVector.getX() + sampleWidth);
                    rayVector.setY(rayVector.getY() + pixelWidth);
                }
                pixelColor /= static_cast<double>(numPixelSamples * numPixelSamples);
                image.setPixelColor(x, y, pixelColor.getR(), pixelColor.getG(), pixelColor.getB());

                rayVector.setX(rayVector.getX() - pixelWidth);
                rayVector.setY(rayVector.getY() - pixelWidth);
            }
            rayVector.setX(rayVector.getX() + pixelWidth);
            rayVector.setY(initialY);
        }
    }
};

#endif //HAYA_LUZ_RAYTRACER_H
