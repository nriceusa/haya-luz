#ifndef HAYA_LUZ_GEOMETRY_H
#define HAYA_LUZ_GEOMETRY_H

#include "Material.h"
#include "../SceneComponent.h"

class Geometry: public SceneComponent {
protected:
    Material material;

    Geometry(const Material& material, const Vector3& location) :
        SceneComponent(location), material(material) {}

    Geometry(const Material& material, const Vector3& location, const Vector3& rotation, const Vector3& scale) :
        SceneComponent(location, rotation, scale), material(material) {}

public:
    const Material& getMaterial() const {
        return material;
    }

    void setMaterial(const Material& newMaterial) {
        material = newMaterial;
    }

    virtual const Vector3 getNormalAt(const Vector3& point) const = 0;

    virtual void print(std::ostream& os) const override = 0;
};

#endif //HAYA_LUZ_GEOMETRY_H