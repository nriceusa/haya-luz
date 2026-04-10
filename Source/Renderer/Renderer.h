#ifndef HAYA_LUZ_RAYTRACER_H
#define HAYA_LUZ_RAYTRACER_H

#define MIN_CLIPPING_DISTANCE 0.001

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

                        Vector3 surfaceRGB = ray.trace(numGlossyBounces);
                        pixelColor += surfaceRGB;
                    }
                    rayVector.setX(rayVector.getX() + sampleWidth);
                    rayVector.setY(rayVector.getY() + pixelWidth);
                }
                pixelColor /= static_cast<double>(numPixelSamples * numPixelSamples);
                pixelColor.setR(Utilities::clamp(pixelColor.getR(), 0, 1));
                pixelColor.setG(Utilities::clamp(pixelColor.getG(), 0, 1));
                pixelColor.setB(Utilities::clamp(pixelColor.getB(), 0, 1));
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
