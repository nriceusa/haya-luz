#ifndef HAYA_LUZ_GEOMETRY_H
#define HAYA_LUZ_GEOMETRY_H

#include "Material.h"
#include "../SceneComponent.h"

class Geometry: public SceneComponent {
private:
    Material& material;

protected:
    Geometry() = default;

    Geometry(Material& material, const Vector3& location) :
        SceneComponent(location), material(material) {}

    Geometry(Material& material, const Vector3& location, const Vector3& rotation, const Vector3& scale) :
        SceneComponent(location, rotation, scale), material(material) {}

public:
    const Material& getMaterial() const {
        return material;
    }

    virtual void print(std::ostream& os) const override = 0;
};

#endif //HAYA_LUZ_GEOMETRY_H