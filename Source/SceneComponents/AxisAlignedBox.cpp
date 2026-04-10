#include <memory>

#include "AxisAlignedBox.h"
#include "Boundable.h"


std::pair<std::unique_ptr<AxisAlignedBox>, std::unique_ptr<AxisAlignedBox>> AxisAlignedBox::split() const {
    const double x = getMaxX() - getMinX();
    const double y = getMaxY() - getMinY();
    const double z = getMaxZ() - getMinZ();
    
    if (x >= y && x >= z) {
        std::deque<Boundable*> leftContents;
        std::deque<Boundable*> rightContents;
        const double midX = getMinX() + x / 2;
        for (auto item : contents) {
            const AxisAlignedBox& componentBoundingVolume = item->getBoundingVolume();
            if (componentBoundingVolume.getMaxX() <= midX) {
                leftContents.push_back(item);
            } else if (componentBoundingVolume.getMinX() >= midX) {
                rightContents.push_back(item);
            } else {
                leftContents.push_back(item);
                rightContents.push_back(item);
            }
        }
        return std::make_pair(
            std::unique_ptr<AxisAlignedBox>(new AxisAlignedBox(
                getMinCorner(), Vector3(midX, getMaxY(), getMaxZ()), leftContents
            )),
            std::unique_ptr<AxisAlignedBox>(new AxisAlignedBox(
                Vector3(midX, getMinY(), getMinZ()), getMaxCorner(), rightContents
            ))
        );
    } else if (y >= x && y >= z) {
        std::deque<Boundable*> lowerContents;
        std::deque<Boundable*> upperContents;
        const double midY = getMinY() + y / 2;
        for (auto item : contents) {
            const AxisAlignedBox& componentBoundingVolume = item->getBoundingVolume();
            if (componentBoundingVolume.getMaxY() <= midY) {
                lowerContents.push_back(item);
            } else if (componentBoundingVolume.getMinY() >= midY) {
                upperContents.push_back(item);
            } else {
                lowerContents.push_back(item);
                upperContents.push_back(item);
            }
        }
        return std::make_pair(
            std::unique_ptr<AxisAlignedBox>(new AxisAlignedBox(
                getMinCorner(), Vector3(getMaxX(), midY, getMaxZ()), lowerContents
            )),
            std::unique_ptr<AxisAlignedBox>(new AxisAlignedBox(
                Vector3(getMinX(), midY, getMinZ()), getMaxCorner(), upperContents
            ))
        );
    } else {
        std::deque<Boundable*> backContents;
        std::deque<Boundable*> frontContents;
        const double midZ = getMinZ() + z / 2;
        for (auto item : contents) {
            const AxisAlignedBox& componentBoundingVolume = item->getBoundingVolume();
            if (componentBoundingVolume.getMaxZ() <= midZ) {
                backContents.push_back(item);
            } else if (componentBoundingVolume.getMinZ() >= midZ) {
                frontContents.push_back(item);
            } else {
                backContents.push_back(item);
                frontContents.push_back(item);
            }
        }
        return std::make_pair(
            std::unique_ptr<AxisAlignedBox>(new AxisAlignedBox(
                getMinCorner(), Vector3(getMaxX(), getMaxY(), midZ), backContents
            )),
            std::unique_ptr<AxisAlignedBox>(new AxisAlignedBox(
                Vector3(getMinX(), getMinY(), midZ), getMaxCorner(), frontContents
            ))
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
