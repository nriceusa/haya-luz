#ifndef HAYA_LUZ_POLYGON_H
#define HAYA_LUZ_POLYGON_H

#include <vector>

#include "Geometry.h"

class Polygon: public Geometry {
private:
    const std::vector<Vector3> points;
    const Vector3 normal;

public:
    Polygon(Material &material, const std::vector<Vector3> &points) :
        points(points),
        normal(Vector3::normalize(Vector3::cross(points[1] - points[0], points[2] - points[0]))),
        Geometry(material, points[0])
    {
        Vector3 location;
        for (Vector3 point : points) {
            location += point;
        }
        location /= points.size();
        setLocation(location);

        // TODO: Implement triangulation and normal calculations
    }

    const Vector3 &getPoint(uint pointIndex) const {
        return points[pointIndex];
    }

    const std::vector<Vector3> &getPoints() const {
        return points;
    }

    const Vector3 &getNormal() const {
        return normal;
    }

    void print(std::ostream &os) const override {
        os << "Polygon:" << std::endl;
        os << "Points:" << std::endl;
        for (const Vector3 &point : points) {
            os << point << std::endl;
        }
        os << "Normal: " << std::endl << normal << std::endl;
    }
};

#endif //HAYA_LUZ_POLYGON_H
