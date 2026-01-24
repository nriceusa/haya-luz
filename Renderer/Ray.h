#ifndef HAYA_LUZ_RAY_H
#define HAYA_LUZ_RAY_H

#define MIN_DIVISION 0.001
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
        } else if (const Polygon* polygon = dynamic_cast<const Polygon*>(&geometry)) {
            // Convert polygon to triangles and test each
            const std::vector<Triangle> triangles = polygon->generateTriangles();
            for (const Triangle& triangle : triangles) {                
                const double distance = hitTriangle(triangle);
                if (distance > MIN_ERROR_DISTANCE) {
                    return distance;
                }
            }
        }
        return -1;
    }

    const Vector3 computeSurface(const uint numRecursions, const Vector3& intersect, const Vector3& normal,
                                 const Material& material) const {
        if (numRecursions <= 0) {
            return {0, 0, 0};
        }
        const Vector3 rayVector = Vector3::normalize(origin - intersect);
        const Vector3 rayDirection = Vector3::normalize(direction);
        
        Vector3 normalVector = Vector3::normalize(normal);
        if (Vector3::dot(rayDirection, normalVector) > 0) {
            normalVector = -normalVector;
        }
        
        // Compute ambience
        const Vector3 ambientLight = scene.getSky().getAmbientLight();
        const Vector3 ambience = material.getEmissionIntensity() * material.getEmissivity() * ambientLight;

        // Compute reflections
        const Vector3 reflectionDirection = rayDirection - (2 * normalVector * (Vector3::dot(rayDirection, normalVector)));
        const Ray reflectionRay(intersect + (normalVector * MIN_ERROR_DISTANCE), reflectionDirection, scene);

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

        Vector3 surfaceRGB = ambience + glossyComponent;

        for (const Light* light : scene.getLights()) {
            const Vector3 lightOffset = light->getLocation() - intersect;
            const Vector3 vectorToLight = Vector3::normalize(lightOffset);

            // Compute shadows
            bool inShadow = false;
            const Ray shadowRay(intersect + (vectorToLight * MIN_ERROR_DISTANCE), lightOffset, scene);
            for (const Geometry* geo : scene.getGeometries()) {
                const Geometry& geometry = *geo;

                const double t = shadowRay.hit(geometry);
                if (t > 0 && t < 1) {
                    inShadow = true;
                    break;
                }
            }
            if (inShadow) {
                continue;
            }

            // Compute diffuse
            double angleToLight = Vector3::dot(normalVector, vectorToLight);
            if (angleToLight < 0) {
                angleToLight = 0;
            }
            const Vector3 diffuse = material.getDiffuse() * light->computeIlluminationAt(intersect) * 
                material.getDiffuseIntensity() * angleToLight;

            // Compute specular highlight
            const Vector3 r = 2 * normalVector * Vector3::dot(normalVector, vectorToLight) - vectorToLight;
            double angleToReflection = Vector3::dot(rayVector, r);
            if (angleToReflection < 0) {
                angleToReflection = 0;
            }
            double specularRoughness = std::max(MIN_DIVISION, material.getSpecularRoughness());
            double anglePower = pow(angleToReflection, (2 / (specularRoughness * specularRoughness)) - 2);
            const Vector3 specular = material.getSpecular() * light->computeIlluminationAt(intersect) *
                material.getSpecularIntensity() * anglePower;

            // Sum lighting components
            surfaceRGB += specular + diffuse;
        }

        surfaceRGB.setR(Utilities::clamp(surfaceRGB.getR(), 0, 1));
        surfaceRGB.setG(Utilities::clamp(surfaceRGB.getG(), 0, 1));
        surfaceRGB.setB(Utilities::clamp(surfaceRGB.getB(), 0, 1));
        return surfaceRGB;
    }
};

#endif //HAYA_LUZ_RAY_H
