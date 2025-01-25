#ifndef HAYA_LUZ_POLYGON_H
#define HAYA_LUZ_POLYGON_H

#include <vector>

#include "Geometry.h"

class Polygon: Geometry {
private:
    const std::vector<Vector3> points;
    const Vector3 normal;

public:
    Polygon(Material &material, const std::vector<Vector3> &points, const Vector3& normal) :
        points(points),
        normal(normal)
    {
        Vector3 location;
        for (Vector3 point : points) {
            location += point;
        }
        location /= points.size();
        setLocation(location);
    }

    const Vector3 &getPoint(size_t pointIndex) const {
        return points[pointIndex];
    }

    const Vector3 &getNormal() const {
        return normal;
    }
};

#endif //HAYA_LUZ_POLYGON_H
