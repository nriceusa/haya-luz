#ifndef HAYA_LUZ_DIRECTIONAL_LIGHT_H
#define HAYA_LUZ_DIRECTIONAL_LIGHT_H

#define MAX_ERROR_DISTANCE 1000

#include "Light.h"

class DirectionalLight: public Light {
public:
    DirectionalLight(const double intensityScalar, const Vector3& intensity, const Vector3& direction) :
        Light(intensityScalar, intensity, Vector3(0, 0, 0), direction) {}

    const Vector3& getLocation() const {
        return -getDirection() * MAX_ERROR_DISTANCE;
    }

    const Vector3 getDirection() const {
        return this->getRotation();
    }

    void print(std::ostream& os) const override {
        os << "Directional Light:" << std::endl;
        os << "intensity scalar: " << this->getIntensityScalar() << std::endl;
        os << "intensity: " << this->getIntensity() << std::endl;
        os << "direction: " << this->getDirection() << std::endl;
    }
};

#endif //HAYA_LUZ_DIRECTIONAL_LIGHT_H