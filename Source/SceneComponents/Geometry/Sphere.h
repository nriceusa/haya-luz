#ifndef HAYA_LUZ_SPHERE_H
#define HAYA_LUZ_SPHERE_H

#include "Geometry.h"

class Sphere : public Geometry {
private:
    double radius;
    Vector3 upAxis;
    Vector3 rightAxis;

    AxisAlignedBox computeBoundingVolume() override {
        Vector3 center = this->getLocation();
        Vector3 minCorner = Vector3(
            center.getX() - radius,
            center.getY() - radius,
            center.getZ() - radius
        );
        Vector3 maxCorner = Vector3(
            center.getX() + radius,
            center.getY() + radius,
            center.getZ() + radius
        );
        return AxisAlignedBox{minCorner, maxCorner};
    }

public:
    Sphere(const Vector3& center) : Sphere(Material(), center) {}

    Sphere(const Vector3& center, double radius) : Sphere(Material(), center, radius) {}

    Sphere(const Material& material, const Vector3& center) :
        Sphere(material, center, 1) {}

    Sphere(const Material& material, const Vector3& center, double radius) :
        Geometry(material, center), radius(radius),
        upAxis(Vector3(0, 1, 0)), rightAxis(Vector3(1, 0, 0)) {}

    const Vector3& getCenter() const {
        return this->getLocation();
    }

    const double getRadius() const {
        return radius;
    }

    void setRadius(const double newRadius) {
        radius = newRadius;
    }

    void transform(const Vector3& translation, const Vector3& rotationAxis, const double angle) override {
        SceneComponent::transform(translation, rotationAxis, angle);

        upAxis = Vector3::normalize(Vector3::rotate(upAxis, rotationAxis, angle));
        rightAxis = Vector3::normalize(Vector3::rotate(rightAxis, rotationAxis, angle));
    }

    const Vector3 getNormalAt(const Vector3& point) const override {
        return (point - this->getLocation()) / radius;
    }

    const Vector2 getUV(const Vector3& point) const override {
        const Vector3 normal = getNormalAt(point);

        const Vector3 forwardAxis = Vector3::normalize(Vector3::cross(upAxis, rightAxis));
        const double localX = Vector3::dot(normal, rightAxis);
        const double localY = Vector3::dot(normal, upAxis);
        const double localZ = Vector3::dot(normal, forwardAxis);

        const double phi = atan2(localZ, localX);
        const double theta = acos(localY);

        const double u = 0.5 + (phi / (2 * M_PI));
        const double v = theta / M_PI;

        return Vector2(u, v);
    }

    void print(std::ostream& os) const override {
        os << "## Sphere" << std::endl;
        os << "center: " << this->getLocation() << std::endl;
        os << "radius: " << radius << std::endl;
        os << this->getMaterial() << std::endl;
    }
};

#endif //HAYA_LUZ_SPHERE_H
