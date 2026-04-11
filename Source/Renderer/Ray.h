#ifndef HAYA_LUZ_RAY_H
#define HAYA_LUZ_RAY_H

#define MIN_DIVISION 0.001

#include <limits>
#include <deque>

#include "../SceneComponents/AxisAlignedBox.h"
#include "../SceneComponents/Boundable.h"
#include "../SceneComponents/Geometry/Geometry.h"
#include "../SceneComponents/Geometry/Polygon.h"
#include "../SceneComponents/Geometry/Triangle.h"
#include "../SceneComponents/Geometry/Sphere.h"
#include "../SceneComponents/Lights/Light.h"
#include "../Scene.h"
#include "../Utilities/Utilities.h"
#include "../Utilities/Vector2.h"
#include "../Utilities/Vector3.h"

class Ray {
private:
    const Vector3 origin;
    const Vector3 direction;
    Scene& scene;

    const double minClippingDistance;
    const double maxClippingDistance;

    double hitBoundingBox(const AxisAlignedBox& box) const {
        const double tMinX = (box.getMinX() - origin.getX()) / direction.getX();
        const double tMaxX = (box.getMaxX() - origin.getX()) / direction.getX();
        const double tMinY = (box.getMinY() - origin.getY()) / direction.getY();
        const double tMaxY = (box.getMaxY() - origin.getY()) / direction.getY();
        const double tMinZ = (box.getMinZ() - origin.getZ()) / direction.getZ();
        const double tMaxZ = (box.getMaxZ() - origin.getZ()) / direction.getZ();

        const double tNearX = std::min(tMinX, tMaxX);
        const double tFarX = std::max(tMinX, tMaxX);
        const double tNearY = std::min(tMinY, tMaxY);
        const double tFarY = std::max(tMinY, tMaxY);
        const double tNearZ = std::min(tMinZ, tMaxZ);
        const double tFarZ = std::max(tMinZ, tMaxZ);

        const double tNear = std::max({tNearX, tNearY, tNearZ});
        const double tFar = std::min({tFarX, tFarY, tFarZ});

        if (tNear > tFar || tFar < 0) {
            return -1;
        } else {
            return std::max(0.0, tNear);
        }
    }

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

        if (
            (Vector3::dot(triangle.getNormal(), Vector3::cross(triangle.getEdge1(), point1ToIntersect)) > 0) &&
            (Vector3::dot(triangle.getNormal(), Vector3::cross(triangle.getEdge2(), point2ToIntersect)) > 0) &&
            (Vector3::dot(triangle.getNormal(), Vector3::cross(triangle.getEdge3(), point3ToIntersect)) > 0)
        ) {
            return rayScalar;
        } else {
            return -1;
        }
    }

    double hitRectangle(
        const double width,
        const double height,
        const Vector3& center,
        const Vector3& normal
    ) const {
        // Compute plane intersect
        const Vector3 originToPlane = center - origin;

        const double rayScalar = Vector3::dot(originToPlane, normal) /
                                 Vector3::dot(direction, normal);

        const Vector3 intersect = origin + (rayScalar * direction);

        if (rayScalar <= 0) {
            return -1;
        }

        // Compute rectangle intersect
        const Vector3 localIntersect = intersect - center;
        const Vector3 rightAxis = Vector3::normalize(Vector3::cross(normal, Vector3(0, 1, 0)));
        const Vector3 upAxis = Vector3::normalize(Vector3::cross(rightAxis, normal));

        const double xDistance = Vector3::dot(localIntersect, rightAxis);
        const double yDistance = Vector3::dot(localIntersect, upAxis);
        
        if (std::abs(xDistance) <= width / 2 && std::abs(yDistance) <= height / 2) {
            return rayScalar;
        } else {
            return -1;
        }
    }

    double hitGeo(const Geometry& geometry) const {
        if (const Sphere* sphere = dynamic_cast<const Sphere*>(&geometry)) {
            return hitSphere(*sphere);
        } else if (const Triangle* triangle = dynamic_cast<const Triangle*>(&geometry)) {
            return hitTriangle(*triangle);
        } else if (const Polygon* polygon = dynamic_cast<const Polygon*>(&geometry)) {
            const std::vector<Triangle> triangles = polygon->generateTriangles();
            for (const Triangle& triangle : triangles) {                
                const double t = hitTriangle(triangle);
                if (t > minClippingDistance) {
                    return t;
                }
            }
        }
        return -1;
    }

    double hitLight(const Light& light) const {
        if (const AreaLight* areaLight = dynamic_cast<const AreaLight*>(&light)) {
            return hitRectangle(
                areaLight->getWidth(),
                areaLight->getHeight(),
                areaLight->getLocation(),
                areaLight->getRotation()
            );
        } else if (const PointLight* pointLight = dynamic_cast<const PointLight*>(&light)) {
            return hitSphere(Sphere(pointLight->getLocation(), pointLight->getRadius()));
        }
        return -1;
    }

    double hitBoundable(const Boundable& boundable) const {
        if (const Geometry* geometry = dynamic_cast<const Geometry*>(&boundable)) {
            return hitGeo(*geometry);
        } else if (const Light* light = dynamic_cast<const Light*>(&boundable)) {
            return hitLight(*light);
        }
        return -1;
    }

public:
    Ray(const Vector3& origin, const Vector3& direction, Scene& scene, double minClippingDistance, double maxClippingDistance) :
        origin(origin),
        direction(direction),
        scene(scene),
        minClippingDistance(minClippingDistance),
        maxClippingDistance(maxClippingDistance) {}

    const Vector3& getOrigin() const {
        return origin;
    }

    const Vector3& getDirection() const {
        return direction;
    }

    Vector3 at(const double position) const {
        return origin + (position * direction);
    }

    const Vector3 trace(uint numRecursions) const {
        double lowestDistance = maxClippingDistance;
        const Boundable* closestBoundable = nullptr;

        std::deque<const AxisAlignedBox*> stack;
        stack.push_back(&scene.getBoundingVolume());
        while (!stack.empty()) {
            const AxisAlignedBox& box = *stack.back();
            stack.pop_back();

            const double boxT = hitBoundingBox(box);
            if (boxT < 0 || lowestDistance <= boxT) {
                continue;
            }

            const auto& children = box.getChildren();
            if (children.first == nullptr && children.second == nullptr) {
                for (const Boundable* item : box.getContents()) {
                    const double boundableT = hitBoundable(*item);
                    if (minClippingDistance < boundableT && boundableT < lowestDistance) {
                        lowestDistance = boundableT;
                        closestBoundable = item;
                    }
                }
            } else {
                stack.push_back(children.first.get());
                stack.push_back(children.second.get());
            }
        }
        
        if (closestBoundable != nullptr) {
            if (const Geometry* geometry = dynamic_cast<const Geometry*>(closestBoundable)) {
                const Vector3 intersection = this->at(lowestDistance);
                const Vector2 uv = geometry->getUV(intersection);
                return this->computeSurface(
                    numRecursions, intersection, geometry->getNormalAt(intersection),
                    uv, geometry->getMaterial()
                );
            } else if (const Light* light = dynamic_cast<const Light*>(closestBoundable)) {
                const Vector3 intersection = this->at(lowestDistance);
                return light->computeIlluminationAt(intersection);
            }
        }
        
        return scene.getSky().getAmbientLight();
    }

    const Vector3 computeSurface(
        const uint numRecursions, const Vector3& intersect, const Vector3& normal,
        const Vector2 uv, const Material& material
    ) const {
        if (numRecursions <= 0) {
            return {0, 0, 0};
        }

        const Vector3 rayVector = Vector3::normalize(origin - intersect);
        const Vector3 rayDirection = Vector3::normalize(direction);
        
        Vector3 normalVector = Vector3::normalize(normal);
        const bool frontFace = Vector3::dot(rayDirection, normalVector) < 0;
        if (!frontFace) {
            normalVector = -normalVector;
        }

        // Compute emission
        Vector3 surfaceRGB = material.getEmissionIntensity() * material.getEmissivity();

        // Compute refractions
        if (material.getTransmission() > 0) {
            const double airIndex = 1.0;
            const double refractionRatio = frontFace
                ? (airIndex / material.getRefractionIndex())
                : (material.getRefractionIndex() / airIndex);
            
            const double cosThetaI = std::min(-Vector3::dot(-rayDirection, normalVector), 1.0);
            const double sin2ThetaT = refractionRatio * refractionRatio * (1 - cosThetaI * cosThetaI);

            if (sin2ThetaT <= 1) {
                const double cosThetaT = sqrt(1 - sin2ThetaT);

                const Vector3 refractionPerp =  refractionRatio * (rayDirection + cosThetaI * normalVector);
                const Vector3 refractionParallel = (
                    -std::sqrt(std::abs(1.0 - refractionPerp.getSquaredLength())) *
                    normalVector
                );
                const Vector3 refractionDirection = Vector3::jitter(
                    refractionPerp + refractionParallel,
                    material.getSpecularRoughness()
                );
                
                const Ray refractionRay(
                    intersect - (normalVector * minClippingDistance),
                    refractionDirection,
                    scene,
                    minClippingDistance,
                    maxClippingDistance
                );
                const Vector3 refractedColor = refractionRay.trace(numRecursions - 1);
                surfaceRGB += material.getTransmission() * refractedColor;
            }
        }

        // Compute diffuse and specular
        const double matComponentsSum = material.getDiffuse() + material.getSpecular();
        if (matComponentsSum <= 0) {
            return surfaceRGB;
        }
        
        const double diffuseProb = material.getDiffuse() / matComponentsSum;
        const double specularProb = material.getSpecular() / matComponentsSum;
        
        thread_local std::mt19937 generator;
        std::uniform_real_distribution<double> distribution(0, 1);
        const double randomValue = distribution(generator);
        if (randomValue < diffuseProb) {
            const Vector3 diffuseDirection = Vector3::normalize(
                Vector3::sampleHemisphere(normalVector)
            );
            const Ray diffusionRay(
                intersect + (normalVector * minClippingDistance),
                diffuseDirection,
                scene,
                minClippingDistance,
                maxClippingDistance
            );
            const Vector3 diffusedColor = diffusionRay.trace(numRecursions - 1);
            const Vector3 albedo = material.getDiffuseIntensity(uv.getU(), uv.getV());

            surfaceRGB += (diffusedColor * albedo * material.getDiffuse()) / diffuseProb;
            
        } else {
            const Vector3 reflectionDirection = Vector3::normalize(
                Vector3::jitter(
                    rayDirection - (2 * normalVector * (Vector3::dot(rayDirection, normalVector))),
                    material.getSpecularRoughness()
                )
            );
            const double reflectionAngle = Vector3::dot(rayDirection, reflectionDirection);

            if (reflectionAngle >= 0) {
                const Ray reflectionRay(
                    intersect + (normalVector * minClippingDistance),
                    reflectionDirection,
                    scene,
                    minClippingDistance,
                    maxClippingDistance
                );
                const Vector3 reflectedColor = reflectionRay.trace(numRecursions - 1);
                surfaceRGB += (reflectedColor * material.getSpecularIntensity() * reflectionAngle * material.getSpecular()) / specularProb;
            }
        }

        return surfaceRGB;
    }
};

#endif //HAYA_LUZ_RAY_H
