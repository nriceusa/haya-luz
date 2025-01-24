#ifndef HAYA_LUZ_RAY_H
#define HAYA_LUZ_RAY_H

#include "../Utilities/Vector3.h"

class Ray {
private:
    const Vector3 origin;
    const Vector3 direction;

public:
    Ray(const Vector3& origin, const Vector3& direction) : origin(origin), direction(direction) {}

    const Vector3& getOrigin() const {
        return origin;
    }

    const Vector3& getDirection() const {
        return direction;
    }

    Vector3 at(double position) const {
        return origin + (position * direction);
    }
};

#endif //HAYA_LUZ_RAY_H