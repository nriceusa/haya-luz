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

    void render(const Scene& scene, Image& image) const {
        const Camera& camera = scene.getActiveCamera();
        Vector3 rayDestination = Vector3::normalize(camera.getTarget() - camera.getOrigin());

        const double xOffset = rayDestination.getZ() * tan(camera.getFieldOfView() / 2);
        const double yOffset = -xOffset * (static_cast<double>(image.getHeight()) / static_cast<double>(image.getWidth()));
        const double pixelWidth = (2 * -xOffset) / static_cast<double>(image.getWidth());
        const double initialX = rayDestination.getX() + xOffset;
        const double initialY = rayDestination.getY() + yOffset;

        rayDestination.setX(initialX);
        for (size_t x = 0; x < image.getWidth(); ++x) {
            rayDestination.setX(rayDestination.getX() + pixelWidth);

            rayDestination.setY(initialY);
            for (size_t y = 0; y < image.getHeight(); ++y) {
                rayDestination.setY(rayDestination.getY() - pixelWidth);

                const Ray ray(camera.getOrigin(), rayDestination, scene);
                double lowestDistance = maxClippingDistance;

                // Check for intersections with polygons
                for (const Geometry* geo : scene.getGeometries()) {
                    const Geometry& geometry = *geo;

                    const double distance = ray.hit(geometry);
                    if (distance < lowestDistance && distance > minClippingDistance) {
                        lowestDistance = distance;
                        const Vector3 intersect = ray.at(distance);
                        const Vector3 normal = geometry.getNormalAt(intersect);

                        // Only accounts for one light
                        Vector3 surfaceColor = ray.computeSurface(glossyBounces, intersect, normal, geometry.getMaterial());
                        image.setPixelRGB(x, y, surfaceColor.getR(), surfaceColor.getG(), surfaceColor.getB());
                    }
                }
            }
        }
    };
};

#endif //HAYA_LUZ_RAYTRACER_H
