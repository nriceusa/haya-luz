#ifndef HAYA_LUZ_POINTLIGHT_H
#define HAYA_LUZ_POINTLIGHT_H

#include "Light.h"

class PointLight : public Light {
public:
    PointLight() = default;

    PointLight(const double intensityScalar, const Vector3& intensity, const Vector3& location) :
        Light(intensityScalar, intensity, location) {}

    void print(std::ostream& os) const override {
        os << "Point Light:" << std::endl;
        os << "intensity scalar: " << getIntensityScalar() << std::endl;
        os << "intensity: " << getIntensity() << std::endl;
        os << "location: " << getLocation() << std::endl;
    }
};

#endif //HAYA_LUZ_POINTLIGHT_H
