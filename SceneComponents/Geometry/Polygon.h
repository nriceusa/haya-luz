#ifndef HAYA_LUZ_POLYGON_H
#define HAYA_LUZ_POLYGON_H

#include <vector>

#include "Geometry.h"
#include "Triangle.h"

class Polygon: public Geometry {
private:
    std::vector<Vector3> points;
    Vector3 normal;

    AxisAlignedPrism computeBoundingVolume() override {
        Vector3 minCorner = points[0];
        Vector3 maxCorner = points[0];
        for (const Vector3& point : points) {
            if (point.getX() < minCorner.getX()) minCorner.setX(point.getX());
            if (point.getY() < minCorner.getY()) minCorner.setY(point.getY());
            if (point.getZ() < minCorner.getZ()) minCorner.setZ(point.getZ());
            if (point.getX() > maxCorner.getX()) maxCorner.setX(point.getX());
            if (point.getY() > maxCorner.getY()) maxCorner.setY(point.getY());
            if (point.getZ() > maxCorner.getZ()) maxCorner.setZ(point.getZ());
        }
        return AxisAlignedPrism{minCorner, maxCorner};
    }

public:
    Polygon(Material& material, std::vector<Vector3>& points) :
        points(points),
        Geometry(material, points[0])
    {
        Vector3 location;
        for (const Vector3& point : points) {
            location += point;
        }
        location /= points.size();
        setLocation(location);

        // Calculate normal
        normal = Vector3(0, 0, 0);
        for (uint i = 0; i < points.size(); ++i) {
            const Vector3& currentPoint = points[i];
            const Vector3& nextPoint = points[(i + 1) % points.size()];
            normal += Vector3::cross(currentPoint - location, nextPoint - location);
        }
        normal = Vector3::normalize(normal);
    }

    const Vector3& getPoint(uint pointIndex) const {
        return points[pointIndex];
    }

    const std::vector<Vector3>& getPoints() const {
        return points;
    }

    const Vector3& getNormal() const {
        return normal;
    }

    const Vector3 getNormalAt(const Vector3& point) const override {
        return getNormal();
    }
    
    void transform(const Vector3& translation, const Vector3& rotationAxis, const double angle) override {
        SceneComponent::transform(translation, rotationAxis, angle);
        for (Vector3& point : points) {
            point = Vector3::rotate(point + translation, rotationAxis, angle);
        }
        normal = Vector3::normalize(Vector3::rotate(normal, rotationAxis, angle));
    }

    std::vector<Triangle> generateTriangles() const {
        std::vector<Triangle> triangles;
        for (uint i = 1; i < points.size() - 1; ++i) {
            const Triangle triangle(this->material, points[0], points[i], points[i + 1]);
            triangles.push_back(triangle);
        }
        return triangles;
    }

    void print(std::ostream& os) const override {
        os << "## Polygon" << std::endl;
        os << "Points:" << std::endl;
        for (const Vector3& point : points) {
            os << point << std::endl;
        }
        os << "normal: " << normal << std::endl;
        os << this->getMaterial() << std::endl;
    }
};

#endif //HAYA_LUZ_POLYGON_H
