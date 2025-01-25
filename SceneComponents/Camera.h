#ifndef HAYA_LUZ_CAMERA_H
#define HAYA_LUZ_CAMERA_H

#include "SceneComponent.h"
#include "../Utilities/Utilities.h"

class Camera: public SceneComponent {
private:
    double fieldOfView;

public:
    Camera() : fieldOfView(Utilities::degreesToRadians(90)) {}

    Camera(const double fovInDegrees, const Vector3 origin, const Vector3 target) :
        SceneComponent(origin, target), fieldOfView(Utilities::degreesToRadians(fovInDegrees)) {}

    double getFieldOfView() const {
        return fieldOfView;
    }
};

#endif //HAYA_LUZ_CAMERA_H
