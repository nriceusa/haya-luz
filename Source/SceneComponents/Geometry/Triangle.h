#ifndef HAYA_LUZ_TRIANGLE_H
#define HAYA_LUZ_TRIANGLE_H

#include "Geometry.h"
#include "../../Utilities/Vector2.h"
#include "../../Utilities/Vector3.h"
#include "../../SceneComponents/Geometry/Material.h"

class Triangle: public Geometry {
private:
    Vector3 point1;
    Vector3 point2;
    Vector3 point3;

    Vector2 uv1;
    Vector2 uv2;
    Vector2 uv3;

    Vector3 normal;

    AxisAlignedBox computeBoundingVolume() override {
        Vector3 minCorner(
            std::min({point1.getX(), point2.getX(), point3.getX()}),
            std::min({point1.getY(), point2.getY(), point3.getY()}),
            std::min({point1.getZ(), point2.getZ(), point3.getZ()})
        );
        Vector3 maxCorner(
            std::max({point1.getX(), point2.getX(), point3.getX()}),
            std::max({point1.getY(), point2.getY(), point3.getY()}),
            std::max({point1.getZ(), point2.getZ(), point3.getZ()})
        );
        return AxisAlignedBox{minCorner, maxCorner};
    }

public:
    Triangle(
        const Material& material,
        const Vector3& point1,
        const Vector3& point2,
        const Vector3& point3
    ) :
        Triangle(
            material,
            point1, point2, point3,
            Vector2(0, 0), Vector2(1, 0), Vector2(0, 1)
        ) {}

    Triangle(
        const Material& material,
        const Vector3& point1,
        const Vector3& point2,
        const Vector3& point3,
        const Vector2& uv1,
        const Vector2& uv2,
        const Vector2& uv3
    ) :
        Geometry(material, (point1 + point2 + point3) / 3),
        point1(point1), point2(point2), point3(point3),
        uv1(uv1), uv2(uv2), uv3(uv3),
        normal(Vector3::normalize(Vector3::cross(point2 - point1, point3 - point1))) {}

    const Vector3& getPoint1() const {
        return point1;
    }

    const Vector3& getPoint2() const {
        return point2;
    }

    const Vector3& getPoint3() const {
        return point3;
    }

    Vector3 getEdge1() const {
        return point2 - point1;
    }

    Vector3 getEdge2() const {
        return point3 - point2;
    }

    Vector3 getEdge3() const {
        return point1 - point3;
    }

    const Vector3& getNormal() const {
        return normal;
    }

    const Vector3 getNormalAt(const Vector3 &point) const override {
        return getNormal();
    }

    const Vector3 getBarycentricCoords(const Vector3& point) const {
        const Vector3 v0 = point2 - point1;
        const Vector3 v1 = point3 - point1;
        const Vector3 v2 = point - point1;

        const double d00 = Vector3::dot(v0, v0);
        const double d01 = Vector3::dot(v0, v1);
        const double d11 = Vector3::dot(v1, v1);
        const double d20 = Vector3::dot(v2, v0);
        const double d21 = Vector3::dot(v2, v1);
        const double determinant = d00 * d11 - d01 * d01;

        const double weight1 = (d11 * d20 - d01 * d21) / determinant;
        const double weight2 = (d00 * d21 - d01 * d20) / determinant;
        const double weight0 = 1.0 - weight1 - weight2;

        return Vector3(weight0, weight1, weight2);
    }

    void transform(const Vector3& translation, const Vector3& rotationAxis, const double angle) override {
        SceneComponent::transform(translation, rotationAxis, angle);
        point1 = Vector3::rotate(point1 + translation, rotationAxis, angle);
        point2 = Vector3::rotate(point2 + translation, rotationAxis, angle);
        point3 = Vector3::rotate(point3 + translation, rotationAxis, angle);
        normal = Vector3::normalize(Vector3::rotate(normal, rotationAxis, angle));
    }

    const Vector2 getUV(const Vector3& point) const override {
        const Vector3 coords = getBarycentricCoords(point);
        return coords.getX() * uv1 + coords.getY() * uv2 + coords.getZ() * uv3;
    }

    void print(std::ostream& os) const override {
        os << "## Triangle" << std::endl;
        os << "point1: " << point1 << std::endl;
        os << "point2: " << point2 << std::endl;
        os << "point3: " << point3 << std::endl;
        os << "normal: " << normal << std::endl;
        os << this->getMaterial() << std::endl;
    }
};

#endif //HAYA_LUZ_TRIANGLE_H
