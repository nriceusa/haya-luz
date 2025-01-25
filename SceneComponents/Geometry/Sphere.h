#ifndef HAYA_LUZ_SPHERE_H
#define HAYA_LUZ_SPHERE_H

#include "Geometry.h"

class Sphere : public Geometry {
private:
    double radius;

public:
    Sphere() : radius(1.0) {}

    Sphere(const Material& material, const Vector3& center, double radius) : Geometry(material, center), radius(radius) {}

    double getRadius() const {
        return radius;
    }

    void setRadius(const double newRadius) {
        radius = newRadius;
    }
};

#endif //HAYA_LUZ_SPHERE_H