#ifndef HAYA_LUZ_SKY_H
#define HAYA_LUZ_SKY_H

#include "SceneComponent.h"

class Sky: public SceneComponent {
private:
    Vector3 color;

public:
    Sky() : color(0, 0, 0) {}

    Sky(Vector3& color) : color(color) {}

    const Vector3& getColor() const {
        return color;
    }
};

#endif //HAYA_LUZ_SKY_H