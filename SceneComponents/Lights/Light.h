#ifndef HAYA_LUZ_LIGHT_H
#define HAYA_LUZ_LIGHT_H

#include "../SceneComponent.h"
#include "../Utilities/Vector3.h"

class Light: public SceneComponent {
private:
    Vector3 intensity;

protected:
    Light() : intensity(1, 1, 1) {}

    Light(const Vector3& intensity) : intensity(intensity) {}

public:
    const Vector3& getIntensity() const {
        return intensity;
    }
};

#endif //HAYA_LUZ_LIGHT_H