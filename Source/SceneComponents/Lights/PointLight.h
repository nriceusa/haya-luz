#ifndef HAYA_LUZ_POINTLIGHT_H
#define HAYA_LUZ_POINTLIGHT_H

#include "../Boundable.h"
#include "Light.h"

class PointLight : public Light, public Boundable {
private:
    double radius;

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
    PointLight() = default;

    PointLight(const double intensityScalar, const Vector3& intensity, const Vector3& location) :
        PointLight(intensityScalar, intensity, location, 0.1) {}

    PointLight(const double intensityScalar, const Vector3& intensity, const Vector3& location, const double radius) :
        Light(intensityScalar, intensity, location), radius(radius),
        Boundable() {}

    double getRadius() const {
        return radius;
    }

    const Vector3 computeIlluminationAt(const Vector3& point) const override {
        const double squaredDistance = (point - getLocation()).getSquaredLength();
        return (this->getIntensity() * this->getIntensityScalar()) / squaredDistance;
    }

    void print(std::ostream& os) const override {
        os << "## Point Light" << std::endl;
        os << "intensity scalar: " << getIntensityScalar() << std::endl;
        os << "intensity: " << getIntensity() << std::endl;
        os << "location: " << getLocation() << std::endl;
        os << "radius: " << getRadius() << std::endl;
    }
};

#endif //HAYA_LUZ_POINTLIGHT_H
