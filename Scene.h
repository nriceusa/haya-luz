#ifndef HAYA_LUZ_SCENE_H
#define HAYA_LUZ_SCENE_H

#include <vector>

#include "SceneComponents/Camera.h"
#include "SceneComponents/Geometry/Geometry.h"
#include "SceneComponents/Geometry/Material.h"
#include "SceneComponents/Geometry/Polygon.h"
#include "SceneComponents/Geometry/Sphere.h"
#include "SceneComponents/Geometry/Triangle.h"
#include "SceneComponents/Lights/DirectionalLight.h"
#include "SceneComponents/Lights/Light.h"
#include "SceneComponents/Lights/PointLight.h"
#include "SceneComponents/Sky.h"

class Scene {
private:
    Sky sky;

    Camera* activeCamera;
    std::vector<Camera> cameras;

    std::vector<const Light*> lights;
    std::vector<DirectionalLight> directionalLights;
    std::vector<PointLight> pointLights;

    std::vector<const Geometry*> geometries;
    std::vector<Polygon> polygons;
    std::vector<Sphere> spheres;
    std::vector<Triangle> triangles;

    std::vector<Material> materials;

    void rotateComponent(SceneComponent& component, const Vector3 translation, const Vector3& rotationAxis, const double angle) {
        component.setLocation(Vector3::rotate(component.getLocation() + translation, rotationAxis, angle));
        component.setRotation(Vector3::rotate(component.getRotation(), rotationAxis, angle));
    }

    void alignToActiveCamera() {
        const Vector3 translation = -activeCamera->getLocation() + Vector3(0, 0, 1);

        // Define the rotation
        const Vector3 cameraRotation = Vector3::normalize(activeCamera->getRotation());
        const Vector3 targetView(0, 0, 0);
        const double angle = acos(Vector3::dot(cameraRotation, targetView));
        Vector3 rotationAxis = Vector3::normalize(Vector3::cross(cameraRotation, targetView));

        // Handle rotation edge case
        if (rotationAxis.getLength() < 0.0001) {
            rotationAxis = Vector3(0, 1, 0);
        }
        
        transform(translation, rotationAxis, angle);
    }

public:
    Scene() = default;

    void transform(const Vector3 translation, const Vector3 rotationAxis, const double angle) {
        for (Camera& camera : cameras) {
            rotateComponent(camera, translation, rotationAxis, angle);
        }

        for (DirectionalLight& light : directionalLights) {
            rotateComponent(light, translation, rotationAxis, angle);
        }

        for (PointLight& light : pointLights) {
            rotateComponent(light, translation, rotationAxis, angle);
        }

        for (Polygon& polygon : polygons) {
            rotateComponent(polygon, translation, rotationAxis, angle);
        }

        for (Sphere& sphere : spheres) {
            rotateComponent(sphere, translation, rotationAxis, angle);
        }

        for (Triangle& triangle : triangles) {
            rotateComponent(triangle, translation, rotationAxis, angle);
        }
    }

    const Sky& getSky() const {
        return sky;
    }

    void setSky(const Sky& newSky) {
        sky = newSky;
    }

    const Camera& getCamera(const uint index) const {
        return cameras[index];
    }

    void addCamera(const Camera& camera) {
        cameras.push_back(camera);

        if (cameras.size() == 1) {
            activeCamera = &cameras[0];
            alignToActiveCamera();
        }
    }

    const Camera& getActiveCamera() const {
        return *activeCamera;
    }

    void setActiveCamera(const uint index) {
        if (index < cameras.size()) {
            activeCamera = &cameras[index];
            alignToActiveCamera();
        }
    }

    void addLight(const Light& light) {
        if (const DirectionalLight* directionalLight = dynamic_cast<const DirectionalLight*>(&light)) {
            directionalLights.push_back(*directionalLight);
            lights.push_back(&directionalLights.back());
        } else if (const PointLight* pointLight = dynamic_cast<const PointLight*>(&light)) {
            pointLights.push_back(*pointLight);
            lights.push_back(&pointLights.back());
        }
    }

    const std::vector<const Light*>& getLights() const {
        return lights;
    }

    void addGeometry(Geometry& geometry) {
        if (Polygon* polygon = dynamic_cast<Polygon*>(&geometry)) {
            polygons.push_back(*polygon);
            geometries.push_back(&polygons.back());
        } else if (Sphere* sphere = dynamic_cast<Sphere*>(&geometry)) {
            spheres.push_back(*sphere);
            geometries.push_back(&spheres.back());
        } else if (Triangle* triangle = dynamic_cast<Triangle*>(&geometry)) {
            triangles.push_back(*triangle);
            geometries.push_back(&triangles.back());
        }
    }

    const std::vector<const Geometry*>& getGeometries() const {
        return geometries;
    }

    Material& getMaterial(const uint index) {
        return materials[index];
    }

    const std::vector<Material>& getMaterials() const {
        return materials;
    }

    void addMaterial(Material& material) {
        materials.push_back(material);
    }

    friend std::ostream& operator<<(std::ostream& os, const Scene& scene) {
        os << "Scene: " << std::endl;
        os << scene.getSky() << std::endl;
        for (const Camera& camera : scene.cameras) {
            if (&camera == scene.activeCamera) {
                os << "<Active Camera>" << std::endl;
            }
            os << camera << std::endl;
        }
        for (const Light* light : scene.getLights()) {
            os << *light << std::endl;
        }
        os << "Geometry: " << std::endl;
        for (const Geometry* geometry : scene.getGeometries()) {
            os << *geometry << std::endl;
        }
        return os;
    }
};

#endif //HAYA_LUZ_SCENE_H
