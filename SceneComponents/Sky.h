#ifndef HAYA_LUZ_SKY_H
#define HAYA_LUZ_SKY_H

#include "SceneComponent.h"

class Sky: public SceneComponent {
private:
    double intensityScalar;
    Vector3 intensity;

public:
    Sky() : intensityScalar(1), intensity(0, 0, 0) {}

    Sky(const Vector3& intensity) : intensityScalar(1), intensity(intensity) {}

    Sky(const double intensityScalar, const Vector3& intensity) :
        intensityScalar(intensityScalar), intensity(intensity) {}

    const double getIntensityScalar() const {
        return intensityScalar;
    }

    const Vector3& getIntensity() const {
        return intensity;
    }

    const Vector3 getAmbientLight() const {
        return intensity * intensityScalar;
    }

    void print(std::ostream& os) const override {
        os << "Sky:" << std::endl;
        os << "intensity scalar: " << getIntensityScalar() << std::endl;
        os << "intensity: " << getIntensity() << std::endl;
    }
};

#endif //HAYA_LUZ_SKY_H