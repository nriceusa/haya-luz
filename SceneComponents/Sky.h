#ifndef HAYA_LUZ_SKY_H
#define HAYA_LUZ_SKY_H

#include "SceneComponent.h"

class Sky: public SceneComponent {
private:
    Vector3 intensity;

public:
    Sky() : intensity(0, 0, 0) {}

    Sky(Vector3& intensity) : intensity(intensity) {}

    const Vector3& getIntensity() const {
        return intensity;
    }
};

#endif //HAYA_LUZ_SKY_H