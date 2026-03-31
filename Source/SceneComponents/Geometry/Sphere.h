#ifndef HAYA_LUZ_SPHERE_H
#define HAYA_LUZ_SPHERE_H

#include "Geometry.h"

class Sphere : public Geometry {
private:
    double radius;

    AxisAlignedBox computeBoundingVolume() override {
        Vector3 center = this->getLocation();
        Vector3 minCorner = Vector3(center.getX() - radius, center.getY() - radius, center.getZ() - radius);
        Vector3 maxCorner = Vector3(center.getX() + radius, center.getY() + radius, center.getZ() + radius);
        return AxisAlignedBox{minCorner, maxCorner};
    }

public:
    Sphere(Material& material, const Vector3& center) :
        Geometry(material, center), radius(1) {}

    Sphere(Material& material, const Vector3& center, double radius) :
        Geometry(material, center), radius(radius) {}

    const Vector3& getCenter() const {
        return this->getLocation();
    }

    const double getRadius() const {
        return radius;
    }

    void setRadius(const double newRadius) {
        radius = newRadius;
    }

    const Vector3 getNormalAt(const Vector3& point) const override {
        return (point - this->getLocation()) / radius;
    }

    const Vector2 getUV(const Vector3& point) const override {
        const Vector3 normal = getNormalAt(point);

        const double phi = atan2(normal.getZ(), normal.getX());
        const double theta = asin(normal.getY());

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