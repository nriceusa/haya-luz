#ifndef HAYA_LUZ_SPHERE_H
#define HAYA_LUZ_SPHERE_H

#include "Geometry.h"

class Sphere : public Geometry {
private:
    double radius;

public:
    Sphere(Material& material, const Vector3& center) : Geometry(material, center), radius(1) {}

    Sphere(Material& material, const Vector3& center, double radius) : Geometry(material, center), radius(radius) {}

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

    void print(std::ostream& os) const override {
        os << "Sphere:" << std::endl;
        os << "center: " << this->getLocation() << std::endl;
        os << "radius: " << radius << std::endl;
        os << this->getMaterial() << std::endl;
    }
};

#endif //HAYA_LUZ_SPHERE_H