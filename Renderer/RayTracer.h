#ifndef HAYA_LUZ_RAYTRACER_H
#define HAYA_LUZ_RAYTRACER_H

#include "../Image/Image.h"
#include "Ray.h"
#include "../Scene.h"

class RayTracer {
private:
    uint glossyBounces;
    double minClippingDistance;
    double maxClippingDistance;

public:
    RayTracer() : glossyBounces(4), minClippingDistance(0), maxClippingDistance(std::numeric_limits<double>::max()) {}

    RayTracer(const uint glossyBounces) :
        glossyBounces(glossyBounces), minClippingDistance(0), maxClippingDistance(std::numeric_limits<double>::max()) {}

    RayTracer(const uint glossyBounces, double minClippingDistance, double maxClippingDistance) :
        glossyBounces(glossyBounces), minClippingDistance(minClippingDistance), maxClippingDistance(maxClippingDistance) {}

    void render(Scene& scene, Image& image) const {
        const Camera& camera = scene.getActiveCamera();
        Vector3 rayVector = Vector3::normalize(camera.getRotation());

        const double xOffset = rayVector.getZ() * tan(camera.getFieldOfView() / 2);
        const double yOffset = -xOffset * (static_cast<double>(image.getHeight()) / static_cast<double>(image.getWidth()));
        const double pixelWidth = (2 * -xOffset) / static_cast<double>(image.getWidth());
        const double initialX = rayVector.getX() + xOffset;
        const double initialY = rayVector.getY() + yOffset;

        rayVector.setX(initialX);
        for (uint x = 0; x < image.getWidth(); ++x) {
            rayVector.setX(rayVector.getX() + pixelWidth);

            rayVector.setY(initialY);
            for (uint y = 0; y < image.getHeight(); ++y) {
                rayVector.setY(rayVector.getY() - pixelWidth);
                const Ray ray(camera.getOrigin(), rayVector, scene);

                // Set background color
                image.setPixelRGB(x, y, scene.getSky().getAmbientLight().getR(), scene.getSky().getAmbientLight().getG(),
                    scene.getSky().getAmbientLight().getB());

                // Check for intersections with geometry
                double lowestDistance = maxClippingDistance;
                for (const Geometry* geo : scene.getGeometries()) {
                    const Geometry& geometry = *geo;

                    const double distance = ray.hit(geometry);

                    if (distance < lowestDistance && distance > minClippingDistance) {
                        lowestDistance = distance;
                        const Vector3 intersect = ray.at(distance);
                        const Vector3 normal = geometry.getNormalAt(intersect);

                        const Vector3 surfaceColor = ray.computeSurface(glossyBounces, intersect, normal, geometry.getMaterial());
                        image.setPixelRGB(x, y, surfaceColor);
                    }
                }
            }
        }
    }
};

#endif //HAYA_LUZ_RAYTRACER_H
