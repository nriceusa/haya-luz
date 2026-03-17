#ifndef AXIS_ALIGNED_BOX_H
#define AXIS_ALIGNED_BOX_H

#include <memory>

#include "../../Utilities/Vector3.h"

class Geometry;

class AxisAlignedBox {
private:
    Vector3 minCorner;
    Vector3 maxCorner;
    std::deque<Geometry*> contents;
    std::pair<std::unique_ptr<AxisAlignedBox>, std::unique_ptr<AxisAlignedBox>> children{nullptr, nullptr};

    std::pair<std::unique_ptr<AxisAlignedBox>, std::unique_ptr<AxisAlignedBox>> split() const;

public:
    AxisAlignedBox() : minCorner(Vector3(0, 0, 0)), maxCorner(Vector3(0, 0, 0)), contents() {}

    AxisAlignedBox(const Vector3& minCorner, const Vector3& maxCorner) :
        minCorner(minCorner), maxCorner(maxCorner) {}

    AxisAlignedBox(const Vector3& minCorner, const Vector3& maxCorner, const std::deque<Geometry*>& contents) :
        minCorner(minCorner), maxCorner(maxCorner), contents(contents) {}

    void recursiveSubdivide(uint subdivLimit, const uint contentsLimit);

    const std::deque<Geometry*>& getContents() const {
        return contents;
    }

    const std::pair<std::unique_ptr<AxisAlignedBox>, std::unique_ptr<AxisAlignedBox>>& getChildren() const {
        return children;
    }

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

#endif // AXIS_ALIGNED_BOX_H
