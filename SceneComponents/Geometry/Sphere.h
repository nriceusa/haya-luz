#ifndef HAYA_LUZ_SPHERE_H
#define HAYA_LUZ_SPHERE_H

#include "Geometry.h"

class Sphere : public Geometry {
private:
    double radius;

public:
    Sphere(Material& material, const Vector3& center) : Geometry(material, center), radius(1) {}

    Sphere(Material& material, const Vector3& center, double radius) : Geometry(material, center), radius(radius) {}

    double getRadius() const {
        return radius;
    }

    void setRadius(const double newRadius) {
        radius = newRadius;
    }

    void print(std::ostream& os) const override {
        os << "Sphere:" << std::endl;
        os << "center: " << this->getLocation() << std::endl;
        os << "radius: " << radius << std::endl;
        os << "material: " << this->getMaterial() << std::endl;
    }
};

#endif //HAYA_LUZ_SPHERE_H