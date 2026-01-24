#ifndef HAYA_LUZ_TRIANGLE_H
#define HAYA_LUZ_TRIANGLE_H

#include "Geometry.h"

class Triangle: public Geometry {
private:
    Vector3 point1;
    Vector3 point2;
    Vector3 point3;

    Vector3 normal;

public:
    Triangle(const Material& material, const Vector3& point1, const Vector3& point2, const Vector3& point3) :
        Geometry(material, (point1 + point2 + point3) / 3),
        point1(point1), point2(point2), point3(point3),
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

    void transform(const Vector3& translation, const Vector3& rotationAxis, const double angle) override {
        SceneComponent::transform(translation, rotationAxis, angle);
        point1 = Vector3::rotate(point1 + translation, rotationAxis, angle);
        point2 = Vector3::rotate(point2 + translation, rotationAxis, angle);
        point3 = Vector3::rotate(point3 + translation, rotationAxis, angle);
        normal = Vector3::normalize(Vector3::rotate(normal, rotationAxis, angle));
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
