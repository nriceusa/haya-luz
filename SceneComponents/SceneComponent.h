#ifndef HAYA_LUZ_SCENE_COMPONENT_H
#define HAYA_LUZ_SCENE_COMPONENT_H

#include "../Utilities/Vector3.h"

class SceneComponent {
private:
    Vector3 location;
    Vector3 rotation;
    Vector3 scale;

protected:
    SceneComponent() : location(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}

    SceneComponent(const Vector3& location) :
        location(location), rotation(0, 0, 0), scale(1, 1, 1) {}

    SceneComponent(const Vector3& location, const Vector3& rotation) :
        location(location), rotation(rotation), scale(1, 1, 1) {}

    SceneComponent(const Vector3& location, const Vector3& rotation, const Vector3& scale) :
        location(location), rotation(rotation), scale(scale) {}

    virtual ~SceneComponent() = default;

public:
    virtual const Vector3& getLocation() const {
        return location;
    }

    virtual const Vector3& getRotation() const {
        return rotation;
    }

    virtual const Vector3& getScale() const {
        return scale;
    }

    virtual void setLocation(const Vector3& newLocation) {
        location = newLocation;
    }

    virtual void setRotation(const Vector3& newRotation) {
        rotation = newRotation;
    }

    virtual void setScale(const Vector3& newScale) {
        scale = newScale;
    }
    
    virtual void transform(const Vector3& translation, const Vector3& rotationAxis, const double angle) {
        location = Vector3::rotate(location + translation, rotationAxis, angle);
        rotation = Vector3::rotate(rotation, rotationAxis, angle);
    }

    virtual void print(std::ostream& os) const = 0;

    friend std::ostream &operator<<(std::ostream& os, const SceneComponent& sceneComponent) {
        sceneComponent.print(os);
        return os;
    }
};

#endif //HAYA_LUZ_SCENE_COMPONENT_H