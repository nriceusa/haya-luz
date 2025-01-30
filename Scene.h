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
    Camera* activeCamera;
    std::vector<Camera> cameras;
    std::vector<Light> lights;
    std::vector<Geometry> geometries;

public:
    Scene() = default;

    void addCamera(const Camera& camera) {
        cameras.push_back(camera);

        if (cameras.size() == 1) {
            activeCamera = &cameras[0];
        }
    }

    const Camera& getCamera(const uint index) const {
        return cameras[index];
    }

    const Camera& getActiveCamera() const {
        return *activeCamera;
    }

    void setActiveCamera(const uint index) {
        if (index < cameras.size()) {
            activeCamera = &cameras[index];
        }
    }

    const Sky& getSky() const {
        return sky;
    }

    void setSky(const Sky& newSky) {
        sky = newSky;
    }

    friend std::ostream& operator<<(std::ostream& os, const Scene& scene) {
        os << "Scene: " << std::endl;

        os << "Sky: " << std::endl << scene.sky << std::endl;

        os << "Cameras: ";
        for (const Camera& camera : scene.cameras) {
            os << std::endl;
            if (&camera == scene.activeCamera) {
                os << "<Active Camera>" << std::endl;
            }
            os << camera << std::endl;
        }

        os << "Lights: " << std::endl;
        for (const Light& light : scene.lights) {
            os << light << std::endl;
        }
        
        os << "Geometry: " << std::endl;
        for (const Geometry& geometry : scene.geometries) {
            os << geometry << std::endl;
        }
        return os;
    }
};

#endif //HAYA_LUZ_SCENE_H
