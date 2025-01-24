#ifndef HAYA_LUZ_SCENE_COMPONENT_H
#define HAYA_LUZ_SCENE_COMPONENT_H

#include "../Utilities/Vector3.h"

class SceneComponent {
private:
    const Vector3 location;
    const Vector3 rotation;
    const Vector3 scale;

protected:
    SceneComponent() : location(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}

    SceneComponent(const Vector3& location) :
        location(location), rotation(0, 0, 0), scale(1, 1, 1) {}

    SceneComponent(const Vector3& location, const Vector3& rotation) :
        location(location), rotation(rotation), scale(1, 1, 1) {}

    SceneComponent(const Vector3& location, const Vector3& rotation, const Vector3& scale) :
        location(location), rotation(rotation), scale(scale) {}

public:
    const Vector3& getLocation() const {
        return location;
    }

    const Vector3& getRotation() const {
        return rotation;
    }

    const Vector3& getScale() const {
        return scale;
    }

    double getLocationX() const {
        return location.getX();
    }

    double getLocationY() const {
        return location.getY();
    }

    double getLocationZ() const {
        return location.getZ();
    }

    double getRotationX() const {
        return rotation.getX();
    }

    double getRotationY() const {
        return rotation.getY();
    }

    double getRotationZ() const {
        return rotation.getZ();
    }

    friend std::ostream &operator<<(std::ostream &os, const SceneComponent &sceneComponent) {
        os << "location: " << sceneComponent.getLocation() << std::endl
           << "rotation: " << sceneComponent.getRotation() << std::endl
           << "scale: " << sceneComponent.getScale() << std::endl;
        return os;
    }
};

#endif //HAYA_LUZ_SCENE_COMPONENT_H