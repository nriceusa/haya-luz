#ifndef HAYA_LUZ_AREALIGHT_H
#define HAYA_LUZ_AREALIGHT_H

#include "../Boundable.h"
#include "Light.h"

class AreaLight : public Light, public Boundable {
private:
    double width;
    double height;

    AxisAlignedBox computeBoundingVolume() override {
        Vector3 right = Vector3::normalize(Vector3::cross(Vector3(0, 1, 0), this->getRotation()));
        if (right.getSquaredLength() == 0) {
            right = Vector3::normalize(Vector3::cross(Vector3(1, 0, 0), this->getRotation()));
        }
        const Vector3 up = Vector3::normalize(Vector3::cross(this->getRotation(), right));

        const Vector3 minCorner = this->getLocation() - (width / 2) * right - (height / 2) * up;
        const Vector3 maxCorner = this->getLocation() + (width / 2) * right + (height / 2) * up;
        
        return AxisAlignedBox{minCorner, maxCorner};
    }
    
    const Vector3 samplePoint() const {
        const Vector3 right = Vector3::normalize(Vector3::cross(Vector3(0, 1, 0), this->getRotation()));
        const Vector3 up = Vector3::normalize(Vector3::cross(this->getRotation(), right));
        
        thread_local std::mt19937 generator;
        thread_local std::uniform_real_distribution<double> xDistribution(-width / 2, width / 2);
        thread_local std::uniform_real_distribution<double> yDistribution(-height / 2, height / 2);
        const double xOffset = xDistribution(generator);
        const double yOffset = yDistribution(generator);

        return this->getLocation() + xOffset * right + yOffset * up;
    }

public:
    AreaLight() : width(1), height(1), Boundable() {}

    AreaLight(const double intensityScalar, const Vector3& intensity,
              const Vector3& location, const Vector3& rotation,
              const double width, const double height) :
        Light(intensityScalar, intensity, location, rotation), width(width), height(height),
        Boundable() {}

    double getWidth() const {
        return width;
    }

    double getHeight() const {
        return height;
    }
    
    const Vector3 computeIlluminationAt(const Vector3& point) const override {
        const double squaredDistance = (point - samplePoint()).getSquaredLength();
        return (this->getIntensity() * this->getIntensityScalar()) / squaredDistance;
    }

    void print(std::ostream& os) const override {
        os << "## Area Light" << std::endl;
        os << "intensity scalar: " << getIntensityScalar() << std::endl;
        os << "intensity: " << getIntensity() << std::endl;
        os << "location: " << getLocation() << std::endl;
        os << "rotation: " << getRotation() << std::endl;
        os << "width: " << getWidth() << std::endl;
        os << "height: " << getHeight() << std::endl;
    }
};

#endif //HAYA_LUZ_AREALIGHT_H