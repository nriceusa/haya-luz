
#ifndef HAYA_LUZ_VECTOR3_H
#define HAYA_LUZ_VECTOR3_H

#include <cmath>
#include <iosfwd>
#include <ostream>

class Vector3 {
private:
    double x;
    double y;
    double z;

public:
    Vector3() : x(0), y(0), z(0) {}
    Vector3(const double x, const double y, const double z) : x(x), y(y), z(z) {}

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    double getZ() const {
        return z;
    }

    void setX(const double newX) {
        Vector3::x = newX;
    }

    void setY(const double newY) {
        Vector3::y = newY;
    }

    void setZ(const double newZ) {
        Vector3::z = newZ;
    }

    double getR() const {
        return getX();
    }

    double getG() const {
        return getY();
    }

    double getB() const {
        return getZ();
    }

    void setR(const double newR) {
        setX(newR);
    }

    void setG(const double newG) {
        setY(newG);
    }

    void setB(const double newB) {
        setZ(newB);
    }

    double getLength() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3 operator-() const {
        return Vector3{-x, -y, -z};
    }

    Vector3& operator+=(const Vector3& vector) {
        x += vector.getX();
        y += vector.getY();
        z += vector.getZ();
        return *this;
    }

    Vector3& operator*=(const double factor) {
        x *= factor;
        y *= factor;
        z *= factor;
        return *this;
    }

    Vector3& operator*=(const Vector3& vector) {
        x *= vector.getX();
        y *= vector.getY();
        z *= vector.getZ();
        return *this;
    }

    Vector3& operator/=(const double dividend) {
        return *this *= 1/dividend;
    }

    bool operator==(const Vector3& vector) const {
        return x == vector.x &&
               y == vector.y &&
               z == vector.z;
    }

    bool operator!=(const Vector3 &vector) const {
        return !(vector == *this);
    }

    friend Vector3 operator+(const Vector3& vectorLeft, const Vector3& vectorRight) {
        return Vector3{vectorLeft.getX() + vectorRight.getX(),
                       vectorLeft.getY() + vectorRight.getY(),
                       vectorLeft.getZ() + vectorRight.getZ()};
    }

    friend Vector3 operator-(const Vector3& vectorLeft, const Vector3& vectorRight) {
        return Vector3{vectorLeft.getX() - vectorRight.getX(),
                       vectorLeft.getY() - vectorRight.getY(),
                       vectorLeft.getZ() - vectorRight.getZ()};
    }

    friend Vector3 operator*(const Vector3& vectorLeft, const Vector3& vectorRight) {
        return Vector3{vectorLeft.getX() * vectorRight.getX(),
                       vectorLeft.getY() * vectorRight.getY(),
                       vectorLeft.getZ() * vectorRight.getZ()};
    }

    friend Vector3 operator*(const double factor, const Vector3& vector) {
        return Vector3{factor * vector.getX(),
                       factor * vector.getY(),
                       factor * vector.getZ()};
    }

    friend Vector3 operator*(const Vector3& vector, const double factor) {
        return factor * vector;
    }

    friend Vector3 operator/(const Vector3& vector, const double dividend) {
        return 1 / dividend * vector;
    }

    static double dot(const Vector3& vectorLeft, const Vector3& vectorRight) {
        return vectorLeft.getX() * vectorRight.getX() +
               vectorLeft.getY() * vectorRight.getY() +
               vectorLeft.getZ() * vectorRight.getZ();
    }

    static Vector3 cross(const Vector3& vectorLeft, const Vector3& vectorRight) {
        return Vector3{vectorLeft.getY() * vectorRight.getZ() - vectorLeft.getZ() * vectorRight.getY(),
                       vectorLeft.getZ() * vectorRight.getX() - vectorLeft.getX() * vectorRight.getZ(),
                       vectorLeft.getX() * vectorRight.getY() - vectorLeft.getY() * vectorRight.getX()};
    }

    static Vector3 normalize(const Vector3& vector) {
        return vector / vector.getLength();
    }

    static Vector3 rotate(const Vector3& vec, const Vector3& rotationAxis, double angle) {
        return vec * cos(angle) + cross(rotationAxis, vec) * sin(angle) + rotationAxis * dot(rotationAxis, vec) * (1 - cos(angle));        
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3& vector) {
        os << vector.getX() << " " << vector.getY() << " " << vector.getZ();
        return os;
    }
};

#endif //HAYA_LUZ_VECTOR3_H
