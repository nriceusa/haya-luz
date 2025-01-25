#ifndef HAYA_LUZ_SCENE_H
#define HAYA_LUZ_SCENE_H

#include <vector>

#include "SceneComponents/Camera.h"
#include "SceneComponents//Geometry/Geometry.h"
#include "SceneComponents/Lights/Light.h"
#include "SceneComponents/Sky.h"

class Scene {
private:
    Sky sky;
    std::vector<Camera> cameras;
    std::vector<Light> lights;
    std::vector<Geometry> Geometry;
};


#endif //HAYA_LUZ_SCENE_H