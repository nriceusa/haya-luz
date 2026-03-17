#ifndef HAYA_LUZ_DIRECTIONAL_LIGHT_H
#define HAYA_LUZ_DIRECTIONAL_LIGHT_H

#define MAX_ERROR_DISTANCE 1000

#include "Light.h"

class DirectionalLight: public Light {
protected:
    void setLocation(const Vector3& newLocation) override {}

public:
    DirectionalLight(const double intensityScalar, const Vector3& intensity, const Vector3& direction) :
        Light(intensityScalar, intensity, -direction * MAX_ERROR_DISTANCE, direction) {}

    const Vector3 getDirection() const {
        return this->getRotation();
    }

    const Vector3 computeIlluminationAt(const Vector3& point) const override {
        return this->getIntensity() * this->getIntensityScalar();
    }

    void print(std::ostream& os) const override {
        os << "## Directional Light" << std::endl;
        os << "intensity scalar: " << this->getIntensityScalar() << std::endl;
        os << "intensity: " << this->getIntensity() << std::endl;
        os << "direction: " << this->getDirection() << std::endl;
    }
};

#endif //HAYA_LUZ_DIRECTIONAL_LIGHT_H