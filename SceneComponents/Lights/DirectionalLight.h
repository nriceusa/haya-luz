#ifndef HAYA_LUZ_DIRECTIONAL_LIGHT_H
#define HAYA_LUZ_DIRECTIONAL_LIGHT_H

#define MAX_ERROR_DISTANCE 1000

#include "Light.h"

class DirectionalLight: public Light {
private:
    const Vector3& target;

public:
    DirectionalLight(const double intensityScalar, const Vector3& intensity, const Vector3& target) :
        target(target), Light(intensityScalar, intensity, Vector3(0, 0, 0), target) {}

    const Vector3 getLocation() const {
        return -target * MAX_ERROR_DISTANCE;
    }

    void print(std::ostream& os) const override {
        os << "Directional Light:" << std::endl;
        os << "intensity scalar: " << this->getIntensityScalar() << std::endl;
        os << "intensity: " << this->getIntensity() << std::endl;
        os << "target: " << this->getLocation() << std::endl;
    }
};

#endif //HAYA_LUZ_DIRECTIONAL_LIGHT_H