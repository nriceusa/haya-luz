#ifndef HAYA_LUZ_POINTLIGHT_H
#define HAYA_LUZ_POINTLIGHT_H

#include "Light.h"

class PointLight : public Light {
public:
    PointLight() = default;

    PointLight(const Vector3& intensity, const Vector3& location) : Light(intensity, location) {}
};

#endif //HAYA_LUZ_POINTLIGHT_H
