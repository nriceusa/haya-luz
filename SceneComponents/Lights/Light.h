#ifndef HAYA_LUZ_LIGHT_H
#define HAYA_LUZ_LIGHT_H

#include "../SceneComponent.h"
#include "../../Utilities/Vector3.h"

class Light: public SceneComponent {
private:
    Vector3 intensity;

protected:
    Light() : intensity(1, 1, 1) {}

    Light(const Vector3& intensity, const Vector3& location) :
        intensity(intensity), SceneComponent(location) {}

    Light(const Vector3& intensity, const Vector3& location, const Vector3& rotation) :
        intensity(intensity), SceneComponent(location, rotation) {}

    Light(const Vector3& intensity, const Vector3& location, const Vector3& rotation, const Vector3& scale) :
        intensity(intensity), SceneComponent(location, rotation, scale) {}

public:
    const Vector3& getIntensity() const {
        return intensity;
    }
};

#endif //HAYA_LUZ_LIGHT_H