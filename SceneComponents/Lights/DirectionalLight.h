#ifndef HAYA_LUZ_DIRECTIONAL_LIGHT_H
#define HAYA_LUZ_DIRECTIONAL_LIGHT_H

#include "Light.h"

class DirectionalLight: public Light {
public:
    DirectionalLight() = default;

    DirectionalLight(const Vector3& intensity, const Vector3& origin, const Vector3& target) : Light(intensity, origin, target) {}
};

#endif //HAYA_LUZ_DIRECTIONAL_LIGHT_H