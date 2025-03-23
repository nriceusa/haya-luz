#ifndef HAYA_LUZ_RAY_H
#define HAYA_LUZ_RAY_H

#define MIN_ERROR_DISTANCE 0.001
#define MAX_ERROR_DISTANCE 1000

#include "../Scene.h"
#include "../SceneComponents/Geometry/Sphere.h"
#include "../Utilities/Utilities.h"
#include "../Utilities/Vector3.h"

class Ray {
private:
    const Vector3 origin;
    const Vector3 direction;
    const Scene& scene;

    double hitSphere(const Sphere& sphere) const {
        Vector3 oc = origin - sphere.getCenter();

        double a = Vector3::dot(direction, direction);
        double halfB = Vector3::dot(oc, direction);
        double c = oc.getLength() * oc.getLength() - (sphere.getRadius() * sphere.getRadius());

        double discriminant = halfB * halfB - a * c;
        if (discriminant < 0) {
            return -1;
        } else {
            return (-halfB - sqrt(discriminant)) / a;
        }
    }

    double hitTriangle(const Triangle& triangle) const {
        // Compute plane intersect
        const Vector3 originToPlane = triangle.getPoint1() - origin;

        const double rayScalar = Vector3::dot(originToPlane, triangle.getNormal()) /
                                 Vector3::dot(direction, triangle.getNormal());

        const Vector3 intersect = origin + (rayScalar * direction);

        if (rayScalar <= 0) {
            return -1;
        }

        // Compute triangle intersect
        const Vector3 point1ToIntersect = intersect - triangle.getPoint1();
        const Vector3 point2ToIntersect = intersect - triangle.getPoint2();
        const Vector3 point3ToIntersect = intersect - triangle.getPoint3();

        if ((Vector3::dot(triangle.getNormal(), Vector3::cross(triangle.getEdge1(), point1ToIntersect)) > 0) &&
            (Vector3::dot(triangle.getNormal(), Vector3::cross(triangle.getEdge2(), point2ToIntersect)) > 0) &&
            (Vector3::dot(triangle.getNormal(), Vector3::cross(triangle.getEdge3(), point3ToIntersect)) > 0)) {
            return rayScalar;
        } else {
            return -1;
        }
    }

public:
    Ray(const Vector3& origin, const Vector3& direction, const Scene& scene) :
        origin(origin), direction(direction), scene(scene) {}

    const Vector3& getOrigin() const {
        return origin;
    }

    const Vector3& getDirection() const {
        return direction;
    }

    Vector3 at(const double position) const {
        return origin + (position * direction);
    }

    double hit(const Geometry& geometry) const {
        if (const Sphere* sphere = dynamic_cast<const Sphere*>(&geometry)) {
            return hitSphere(*sphere);
        } else if (const Triangle* triangle = dynamic_cast<const Triangle*>(&geometry)) {
            return hitTriangle(*triangle);
        } else {
            return -1;
        }
    }

    const Vector3 computeSurface(const uint numRecursions, const Vector3& intersect, const Vector3& normal,
                                 const Material& material) const {
        if (numRecursions <= 0) {
            return {0, 0, 0};
        }

        const Light& light = *scene.getLights()[0];  // Only accounts for one light
        const Vector3 vectorToLight = Vector3::normalize(light.getLocation() - intersect);
        const Vector3 normalVector = Vector3::normalize(normal);
        const Vector3 rayVector = Vector3::normalize(origin - intersect);
        const Vector3 rayDirection = Vector3::normalize(direction);

        std::cout << std::endl << "Light: " << light;
        std::cout << "Light location: " << light.getLocation() << std::endl;
        std::cout << "Vector to light: " << vectorToLight << std::endl;

        // Compute shadows
        bool inShadow = false;
        const Vector3 shadowVector = Vector3::normalize(light.getLocation() - intersect);
        const Ray shadowRay(intersect + (shadowVector * MIN_ERROR_DISTANCE), light.getLocation(), scene);
        for (const Geometry* geo : scene.getGeometries()) {
            const Geometry& geometry = *geo;

            const double t = shadowRay.hit(geometry);
            if (t > 0) {
                inShadow = true;
                break;
            }
        }

        // Compute reflections
        const Vector3 reflectionDirection = rayDirection - (2 * normalVector * (Vector3::dot(rayDirection, normalVector)));
        const Ray reflectionRay(intersect + (normalVector * MIN_ERROR_DISTANCE), reflectionDirection, scene);

        const Vector3 ambientLight = scene.getSky().getAmbientLight();
        Vector3 reflectedColor = ambientLight;
        double lowestDistance = MAX_ERROR_DISTANCE;
        for (const Geometry* geo : scene.getGeometries()) {
            const Geometry& geometry = *geo;

            const double distance = reflectionRay.hit(geometry);
            if (distance < lowestDistance && distance > MIN_ERROR_DISTANCE) {
                lowestDistance = distance;
                const Vector3 reflectionIntersect = reflectionRay.at(distance);
                reflectedColor = reflectionRay.computeSurface(numRecursions - 1, reflectionIntersect,
                    geometry.getNormalAt(reflectionIntersect), geometry.getMaterial());
            }
        }
        const Vector3 glossyComponent = material.getSpecular() * reflectedColor;

        // Compute diffuse
        double angleToLight = Vector3::dot(normalVector, vectorToLight);
        if (angleToLight < 0) {
            angleToLight = 0;
        }
        const Vector3 diffuse = material.getDiffuse() * light.getIntensity() * material.getDiffuseIntensity() * angleToLight;

        std::cout << "Angle to light: " << angleToLight << std::endl;
        std::cout << "Diffuse: " << diffuse << std::endl;

        // Compute ambience
        const Vector3 ambience = material.getEmissionIntensity() * material.getEmissivity() * ambientLight;

        // Compute specular highlight
        const Vector3 r = 2 * normalVector * Vector3::dot(normalVector, vectorToLight) - vectorToLight;
        double angleToReflection = Vector3::dot(rayVector, r);
        if (angleToReflection < 0) {
            angleToReflection = 0;
        }
        const Vector3 specular = material.getSpecular() * light.getIntensity() *
            material.getSpecularIntensity() * pow(angleToReflection, material.getSpecularRoughness());

        // Sum lighting components
        Vector3 surfaceColor = ambience + glossyComponent;
        if (!inShadow) {
            surfaceColor += specular + diffuse;
        }
        surfaceColor.setR(Utilities::clamp(surfaceColor.getR(), 0, 1));
        surfaceColor.setG(Utilities::clamp(surfaceColor.getG(), 0, 1));
        surfaceColor.setB(Utilities::clamp(surfaceColor.getB(), 0, 1));
        return surfaceColor;
    }
};

#endif //HAYA_LUZ_RAY_H