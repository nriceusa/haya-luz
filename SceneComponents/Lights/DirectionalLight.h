#ifndef HAYA_LUZ_DIRECTIONAL_LIGHT_H
#define HAYA_LUZ_DIRECTIONAL_LIGHT_H

#include "Light.h"

class DirectionalLight: public Light {
public:
    DirectionalLight() = default;

    DirectionalLight(const double intensityScalar, const Vector3& intensity, const Vector3& target) :
        Light(intensityScalar, intensity, Vector3(0, 0, 0), target) {}

    void print(std::ostream& os) const override {
        os << "Directional Light:" << std::endl;
        os << "intensity scalar: " << this->getIntensityScalar() << std::endl;
        os << "intensity: " << this->getIntensity() << std::endl;
        os << "target: " << this->getLocation() << std::endl;
    }
};

#endif //HAYA_LUZ_DIRECTIONAL_LIGHT_H