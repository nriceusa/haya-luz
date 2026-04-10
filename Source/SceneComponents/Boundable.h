#ifndef BOUNDABLE_H
#define BOUNDABLE_H

#include "AxisAlignedBox.h"

class Boundable {
private:
    AxisAlignedBox boundingVolume;
    bool boundingVolumeUpdated = false;

    virtual AxisAlignedBox computeBoundingVolume() = 0;

protected:
    Boundable() = default;

public:
    const AxisAlignedBox& getBoundingVolume() {
        if (!boundingVolumeUpdated) {
            boundingVolume = computeBoundingVolume();
            boundingVolumeUpdated = true;
        }
        return boundingVolume;
    }
};

#endif //BOUNDABLE_H
