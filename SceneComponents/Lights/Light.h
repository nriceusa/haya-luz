#ifndef HAYA_LUZ_LIGHT_H
#define HAYA_LUZ_LIGHT_H

#include "../SceneComponent.h"
#include "../../Utilities/Vector3.h"

class Light: public SceneComponent {
private:
    Vector3 intensity;
    double intensityScalar;

protected:
    Light() : intensityScalar(1), intensity(1, 1, 1) {}

    Light(const double intensityScalar, const Vector3& intensity, const Vector3& location) :
        intensityScalar(intensityScalar), intensity(intensity), SceneComponent(location) {}

    Light(const double intensityScalar, const Vector3& intensity, const Vector3& location,
          const Vector3& rotation) :
        intensityScalar(intensityScalar), intensity(intensity), SceneComponent(location, rotation) {}

    Light(const double intensityScalar, const Vector3& intensity, const Vector3& location,
          const Vector3& rotation, const Vector3& scale) :
        intensityScalar(intensityScalar), intensity(intensity), SceneComponent(location, rotation, scale) {}
    
    const double getIntensityScalar() const {
        return intensityScalar;
    }

    const Vector3 getIntensity() const {
        return intensity * intensityScalar;
    }

public:
    virtual const Vector3 computeIlluminationAt(const Vector3& point) const = 0;

    virtual void print(std::ostream& os) const override = 0;
};

#endif //HAYA_LUZ_LIGHT_H