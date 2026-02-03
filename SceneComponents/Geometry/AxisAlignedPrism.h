#ifndef AXIS_ALIGNED_PRISM_H
#define AXIS_ALIGNED_PRISM_H

#include "../../Utilities/Vector3.h"

class AxisAlignedPrism {
private:
    Vector3 minCorner;
    Vector3 maxCorner;

public:
    AxisAlignedPrism() : minCorner(Vector3(0, 0, 0)), maxCorner(Vector3(0, 0, 0)) {}

    AxisAlignedPrism(const Vector3& minCorner, const Vector3& maxCorner) :
        minCorner(minCorner), maxCorner(maxCorner) {}

    const Vector3& getMinCorner() const {
        return minCorner;
    }

    const Vector3& getMaxCorner() const {
        return maxCorner;
    }

    const double getMinX() const {
        return minCorner.getX();
    }

    const double getMinY() const {
        return minCorner.getY();
    }

    const double getMinZ() const {
        return minCorner.getZ();
    }

    const double getMaxX() const {
        return maxCorner.getX();
    }

    const double getMaxY() const {
        return maxCorner.getY();
    }

    const double getMaxZ() const {
        return maxCorner.getZ();
    }

    void setMinCorner(const Vector3& newMinCorner) {
        minCorner = newMinCorner;
    }

    void setMaxCorner(const Vector3& newMaxCorner) {
        maxCorner = newMaxCorner;
    }

    void setMinX(const double newMinX) {
        minCorner.setX(newMinX);
    }

    void setMinY(const double newMinY) {
        minCorner.setY(newMinY);
    }

    void setMinZ(const double newMinZ) {
        minCorner.setZ(newMinZ);
    }

    void setMaxX(const double newMaxX) {
        maxCorner.setX(newMaxX);
    }

    void setMaxY(const double newMaxY) {
        maxCorner.setY(newMaxY);
    }

    void setMaxZ(const double newMaxZ) {
        maxCorner.setZ(newMaxZ);
    }
};

#endif // AXIS_ALIGNED_PRISM_H
