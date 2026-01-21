#ifndef HAYA_LUZ_POINTLIGHT_H
#define HAYA_LUZ_POINTLIGHT_H

#include "Light.h"

class PointLight : public Light {
public:
    PointLight() = default;

    PointLight(const double intensityScalar, const Vector3& intensity, const Vector3& location) :
        Light(intensityScalar, intensity, location) {}

    const Vector3& computeRadianceAt(const Vector3& point) const override {
        const double squaredDistance = (point - getLocation()).getSquaredLength();
        return (this->getIntensity() * this->getIntensityScalar()) / squaredDistance;
    }

    void print(std::ostream& os) const override {
        os << "Point Light:" << std::endl;
        os << "intensity scalar: " << getIntensityScalar() << std::endl;
        os << "intensity: " << getIntensity() << std::endl;
        os << "location: " << getLocation() << std::endl;
    }
};

#endif //HAYA_LUZ_POINTLIGHT_H
