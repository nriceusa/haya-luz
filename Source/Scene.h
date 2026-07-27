#ifndef HAYA_LUZ_SCENE_H
#define HAYA_LUZ_SCENE_H

#include <vector>

#include "SceneComponents/Camera.h"
#include "SceneComponents/AxisAlignedBox.h"
#include "SceneComponents/Geometry/Geometry.h"
#include "SceneComponents/Geometry/Material.h"
#include "SceneComponents/Geometry/Polygon.h"
#include "SceneComponents/Geometry/Sphere.h"
#include "SceneComponents/Geometry/Triangle.h"
#include "SceneComponents/Lights/AreaLight.h"
#include "SceneComponents/Lights/DirectionalLight.h"
#include "SceneComponents/Lights/PointLight.h"
#include "SceneComponents/Lights/Light.h"
#include "SceneComponents/Lights/PointLight.h"
#include "SceneComponents/Sky.h"

class Scene {
private:
    void initializeBoundingVolume(const uint volumeSubdivLimit, const uint volumeContentsLimit) {
        if (boundables.empty()) {
            boundingVolume = AxisAlignedBox();
        } else {
            double minX = boundables[0]->getBoundingVolume().getMinX();
            double minY = boundables[0]->getBoundingVolume().getMinY();
            double minZ = boundables[0]->getBoundingVolume().getMinZ();
            double maxX = boundables[0]->getBoundingVolume().getMaxX();
            double maxY = boundables[0]->getBoundingVolume().getMaxY();
            double maxZ = boundables[0]->getBoundingVolume().getMaxZ();
            for (Boundable* boundable : boundables) {
                const AxisAlignedBox& boundableVolume = boundable->getBoundingVolume();
                minX = std::min(minX, boundableVolume.getMinX());
                minY = std::min(minY, boundableVolume.getMinY());
                minZ = std::min(minZ, boundableVolume.getMinZ());
                maxX = std::max(maxX, boundableVolume.getMaxX());
                maxY = std::max(maxY, boundableVolume.getMaxY());
                maxZ = std::max(maxZ, boundableVolume.getMaxZ());
            }
            boundingVolume = AxisAlignedBox(Vector3(minX, minY, minZ), Vector3(maxX, maxY, maxZ), boundables);
            boundingVolume.recursiveSubdivide(volumeSubdivLimit, volumeContentsLimit);
        }
    }

    std::deque<Boundable*> boundables;
    AxisAlignedBox boundingVolume;
    bool boundingVolumeUpdated = false;
    const uint volumeSubdivLimit;
    const uint volumeContentsLimit;

    Sky sky;

    Camera* activeCamera;
    std::deque<Camera> cameras;

    std::deque<Light*> lights;
    std::deque<AreaLight> areaLights;
    std::deque<DirectionalLight> directionalLights;
    std::deque<PointLight> pointLights;

    std::deque<Geometry*> geometries;
    std::deque<Polygon> polygons;
    std::deque<Sphere> spheres;
    std::deque<Triangle> triangles;

    std::unordered_map<uint, Material> materials;
    std::unordered_map<uint, Image> textures;

public:
    Scene() : volumeSubdivLimit(20), volumeContentsLimit(3) {};

    const AxisAlignedBox& getBoundingVolume() {
        if (!boundingVolumeUpdated) {
            initializeBoundingVolume(volumeSubdivLimit, volumeContentsLimit);
            boundingVolumeUpdated = true;
        }
        return boundingVolume;
    }

    void transform(const Vector3 translation, const Vector3 rotationAxis, const double angle) {
        for (Camera& camera : cameras) {
            camera.transform(translation, rotationAxis, angle);
        }

        for (AreaLight& light : areaLights) {
            light.transform(translation, rotationAxis, angle);
        }

        for (DirectionalLight& light : directionalLights) {
            light.transform(translation, rotationAxis, angle);
        }

        for (PointLight& light : pointLights) {
            light.transform(translation, rotationAxis, angle);
        }

        for (Polygon& polygon : polygons) {
            polygon.transform(translation, rotationAxis, angle);
        }

        for (Sphere& sphere : spheres) {
            sphere.transform(translation, rotationAxis, angle);
        }

        for (Triangle& triangle : triangles) {
            triangle.transform(translation, rotationAxis, angle);
        }
    }

    void alignToActiveCamera() {
        const Vector3 translation = -activeCamera->getLocation() + Vector3(0, 0, 1);

        // Define the rotation
        const Vector3 cameraRotation = Vector3::normalize(activeCamera->getRotation());
        const Vector3 targetView(0, 0, -1);
        const double angle = acos(Vector3::dot(cameraRotation, targetView));

        // Calculate cross product first without normalizing
        const Vector3 crossProduct = Vector3::cross(cameraRotation, targetView);
        Vector3 rotationAxis;

        // Handle rotation edge case (vectors are parallel)
        if (crossProduct.getLength() < 0.0001) {
            rotationAxis = Vector3(0, 1, 0);
        } else {
            rotationAxis = Vector3::normalize(crossProduct);
        }
        
        transform(translation, rotationAxis, angle);
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

    void addCamera(Camera&& camera) {
        cameras.push_back(camera);

        if (cameras.size() == 1) {
            activeCamera = &cameras[0];
        }
    }

    const Camera& getActiveCamera() const {
        return *activeCamera;
    }

    void setActiveCamera(const uint index) {
        if (index < cameras.size()) {
            activeCamera = &cameras[index];
        }
    }

    void addLight(DirectionalLight&& light) {
        directionalLights.push_back(std::move(light));
        lights.push_back(&directionalLights.back());
    }

    void addLight(PointLight&& light) {
        pointLights.push_back(std::move(light));
        lights.push_back(&pointLights.back());
        boundables.push_back(&pointLights.back());
    }

    void addLight(AreaLight&& light) {
        areaLights.push_back(std::move(light));
        lights.push_back(&areaLights.back());
        boundables.push_back(&areaLights.back());
    }

    const std::deque<Light*>& getLights() const {
        return lights;
    }

    const std::deque<DirectionalLight>& getDirectionalLights() const {
        return directionalLights;
    }

    const std::deque<PointLight>& getPointLights() const {
        return pointLights;
    }

    void addGeometry(Polygon&& geometry) {
        polygons.push_back(std::move(geometry));
        geometries.push_back(&polygons.back());
        boundables.push_back(&polygons.back());
    }

    void addGeometry(Sphere&& geometry) {
        spheres.push_back(std::move(geometry));
        geometries.push_back(&spheres.back());
        boundables.push_back(&spheres.back());
    }

    void addGeometry(Triangle&& geometry) {
        triangles.push_back(std::move(geometry));
        geometries.push_back(&triangles.back());
        boundables.push_back(&triangles.back());
    }

    const std::deque<Geometry*>& getGeometries() const {
        return geometries;
    }

    Material& getMaterial(const uint index) {
        return materials.at(index);
    }

    const std::unordered_map<uint, Material>& getMaterials() const {
        return materials;
    }

    void addMaterial(uint id, Material&& material) {
        materials[id] = material;
    }

    const Image& getTexture(const uint index) const {
        return textures.at(index);
    }

    const std::unordered_map<uint, Image>& getTextures() const {
        return textures;
    }

    void addTexture(uint id, Image&& texture) {
        textures[id] = texture;
    }

    friend std::ostream& operator<<(std::ostream& os, const Scene& scene) {
        os << "# Scene" << std::endl;
        os << scene.getSky() << std::endl;
        for (const Camera& camera : scene.cameras) {
            if (&camera == scene.activeCamera) {
                os << "**Active Camera**" << std::endl;
            }
            os << camera << std::endl;
        }
        os << "# Lights" << std::endl;
        for (const Light* light : scene.getLights()) {
            os << *light << std::endl;
        }
        os << "# Geometry" << std::endl;
        for (const Geometry* geometry : scene.getGeometries()) {
            os << *geometry << std::endl;
        }
        os << "# Number of Textures" << std::endl;
        os << scene.getTextures().size() << std::endl;

        return os;
    }
};

#endif //HAYA_LUZ_SCENE_H
