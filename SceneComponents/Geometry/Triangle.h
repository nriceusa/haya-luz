#ifndef HAYA_LUZ_TRIANGLE_H
#define HAYA_LUZ_TRIANGLE_H

#include "Geometry.h"

class Triangle: public Geometry {
private:
    const Vector3 point1;
    const Vector3 point2;
    const Vector3 point3;

    const Vector3 edge1;
    const Vector3 edge2;
    const Vector3 edge3;

    const Vector3 normal;

public:
    Triangle(Material &material, const Vector3 &point1, const Vector3 &point2, const Vector3 &point3) :
        Geometry(material, (point1 + point2 + point3) / 3),
        point1(point1), point2(point2), point3(point3),
        edge1(point2 - point1), edge2(point3 - point2),
        edge3(point1 - point3),
        normal(Vector3::normalize(Vector3::cross(point2 - point1, point3 - point1))) {}

    const Vector3 &getPoint1() const {
        return point1;
    }

    const Vector3 &getPoint2() const {
        return point2;
    }

    const Vector3 &getPoint3() const {
        return point3;
    }

    const Vector3 &getEdge1() const {
        return edge1;
    }

    const Vector3 &getEdge2() const {
        return edge2;
    }

    const Vector3 &getEdge3() const {
        return edge3;
    }

    const Vector3 &getNormal() const {
        return normal;
    }

    void print(std::ostream& os) const override {
        os << "Triangle:" << std::endl;
        os << "point1: " << point1 << std::endl;
        os << "point2: " << point2 << std::endl;
        os << "point3: " << point3 << std::endl;
        os << "normal: " << normal << std::endl;
    }
};

#endif //HAYA_LUZ_TRIANGLE_H
