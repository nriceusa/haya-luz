#include <memory>

#include "AxisAlignedBox.h"
#include "Geometry.h"


std::pair<std::unique_ptr<AxisAlignedBox>, std::unique_ptr<AxisAlignedBox>> AxisAlignedBox::split() const {
    const double x = getMaxX() - getMinX();
    const double y = getMaxY() - getMinY();
    const double z = getMaxZ() - getMinZ();
    
    if (x >= y && x >= z) {
        std::deque<Geometry*> leftContents;
        std::deque<Geometry*> rightContents;
        const double midX = getMinX() + x / 2;
        for (Geometry* geometry : contents) {
            const AxisAlignedBox& geometryBoundingVolume = geometry->getBoundingVolume();
            if (geometryBoundingVolume.getMaxX() <= midX) {
                leftContents.push_back(geometry);
            } else if (geometryBoundingVolume.getMinX() >= midX) {
                rightContents.push_back(geometry);
            } else {
                leftContents.push_back(geometry);
                rightContents.push_back(geometry);
            }
        }
        return std::make_pair(
            std::unique_ptr<AxisAlignedBox>(new AxisAlignedBox(getMinCorner(), Vector3(midX, getMaxY(), getMaxZ()), leftContents)),
            std::unique_ptr<AxisAlignedBox>(new AxisAlignedBox(Vector3(midX, getMinY(), getMinZ()), getMaxCorner(), rightContents))
        );
    } else if (y >= x && y >= z) {
        std::deque<Geometry*> lowerContents;
        std::deque<Geometry*> upperContents;
        const double midY = getMinY() + y / 2;
        for (Geometry* geometry : contents) {
            const AxisAlignedBox& geometryBoundingVolume = geometry->getBoundingVolume();
            if (geometryBoundingVolume.getMaxY() <= midY) {
                lowerContents.push_back(geometry);
            } else if (geometryBoundingVolume.getMinY() >= midY) {
                upperContents.push_back(geometry);
            } else {
                lowerContents.push_back(geometry);
                upperContents.push_back(geometry);
            }
        }
        return std::make_pair(
            std::unique_ptr<AxisAlignedBox>(new AxisAlignedBox(getMinCorner(), Vector3(getMaxX(), midY, getMaxZ()), lowerContents)),
            std::unique_ptr<AxisAlignedBox>(new AxisAlignedBox(Vector3(getMinX(), midY, getMinZ()), getMaxCorner(), upperContents))
        );
    } else {
        std::deque<Geometry*> backContents;
        std::deque<Geometry*> frontContents;
        const double midZ = getMinZ() + z / 2;
        for (Geometry* geometry : contents) {
            const AxisAlignedBox& geometryBoundingVolume = geometry->getBoundingVolume();
            if (geometryBoundingVolume.getMaxZ() <= midZ) {
                backContents.push_back(geometry);
            } else if (geometryBoundingVolume.getMinZ() >= midZ) {
                frontContents.push_back(geometry);
            } else {
                backContents.push_back(geometry);
                frontContents.push_back(geometry);
            }
        }
        return std::make_pair(
            std::unique_ptr<AxisAlignedBox>(new AxisAlignedBox(getMinCorner(), Vector3(getMaxX(), getMaxY(), midZ), backContents)),
            std::unique_ptr<AxisAlignedBox>(new AxisAlignedBox(Vector3(getMinX(), getMinY(), midZ), getMaxCorner(), frontContents))
        );
    }
}

void AxisAlignedBox::recursiveSubdivide(uint subdivLimit, const uint contentsLimit) {
    if (contents.size() <= contentsLimit || subdivLimit <= 0) {
        return;
    }
    children = split();
    children.first->recursiveSubdivide(subdivLimit - 1, contentsLimit);
    children.second->recursiveSubdivide(subdivLimit - 1, contentsLimit);
}
