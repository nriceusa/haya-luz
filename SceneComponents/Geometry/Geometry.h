#ifndef HAYA_LUZ_GEOMETRY_H
#define HAYA_LUZ_GEOMETRY_H

#include "AxisAlignedPrism.h"
#include "Material.h"
#include "../SceneComponent.h"

class Geometry: public SceneComponent {
private:
    bool boundingVolumeUpdated = false;

protected:
    Material material;
    AxisAlignedPrism boundingVolume;

    Geometry(const Material& material, const Vector3& location) :
    SceneComponent(location), material(material), boundingVolume(AxisAlignedPrism()) {}
    
    Geometry(
        const Material& material,
        const Vector3& location,
        const Vector3& rotation,
        const Vector3& scale,
        const AxisAlignedPrism& boundingVolume) :
        SceneComponent(location, rotation, scale), material(material), boundingVolume(boundingVolume) {}
    
    virtual AxisAlignedPrism computeBoundingVolume() = 0;

public:
    const Material& getMaterial() const {
        return material;
    }
    
    void setMaterial(const Material& newMaterial) {
        material = newMaterial;
    }

    const AxisAlignedPrism& getBoundingVolume() {
        if (!boundingVolumeUpdated) {
            boundingVolume = computeBoundingVolume();
            boundingVolumeUpdated = true;
        }
        return boundingVolume;
    }

    virtual const Vector3 getNormalAt(const Vector3& point) const = 0;

    virtual void print(std::ostream& os) const override = 0;
};

#endif //HAYA_LUZ_GEOMETRY_H