#ifndef HAYA_LUZ_CAMERA_H
#define HAYA_LUZ_CAMERA_H

#include "SceneComponent.h"
#include "../Utilities/Utilities.h"

class Camera: public SceneComponent {
private:
    double fieldOfView;

public:
    Camera() : fieldOfView(Utilities::degreesToRadians(90)), SceneComponent(Vector3(0, 0, 0), Vector3(0, 0, -1)) {}

    Camera(const double fovInDegrees, const Vector3 origin, const Vector3 target) :
        SceneComponent(origin, target - origin), fieldOfView(Utilities::degreesToRadians(fovInDegrees)) {}

    double getFieldOfView() const {
        return fieldOfView;
    }

    const Vector3& getOrigin() const {
        return getLocation();
    }

    const Vector3 getTarget() const {
        return getRotation() + getLocation();
    }

    void print(std::ostream& os) const override {
        os << "Camera:" << std::endl;
        os << "origin: " << this->getLocation() << std::endl;
        os << "target: " << this->getRotation() << std::endl;
        os << "field of view: " << Utilities::radiansToDegrees(this->getFieldOfView()) << std::endl;
    }
};

#endif //HAYA_LUZ_CAMERA_H
