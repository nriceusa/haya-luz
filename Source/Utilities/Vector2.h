#ifndef HAYA_LUZ_VECTOR2_H
#define HAYA_LUZ_VECTOR2_H

class Vector2 {
private:
    double u;
    double v;

public:
    Vector2() : u(0), v(0) {}
    Vector2(const double u, const double v) : u(u), v(v) {}

    double getU() const {
        return u;
    }

    double getV() const {
        return v;
    }

    void setU(const double newU) {
        Vector2::u = newU;
    }

    void setV(const double newV) {
        Vector2::v = newV;
    }

    Vector2 operator-() const {
        return Vector2{-u, -v};
    }

    Vector2& operator+=(const Vector2& vector) {
        u += vector.getU();
        v += vector.getV();
        return *this;
    }

    Vector2& operator*=(const double factor) {
        u *= factor;
        v *= factor;
        return *this;
    }

    Vector2& operator/=(const double dividend) {
        return *this *= 1/dividend;
    }

    bool operator==(const Vector2& vector) const {
        return u == vector.u &&
               v == vector.v;
    }

    bool operator!=(const Vector2 &vector) const {
        return !(vector == *this);
    }

    friend Vector2 operator+(const Vector2& vectorLeft, const Vector2& vectorRight) {
        return Vector2{vectorLeft.getU() + vectorRight.getU(),
                       vectorLeft.getV() + vectorRight.getV()};
    }

    friend Vector2 operator-(const Vector2& vectorLeft, const Vector2& vectorRight) {
        return Vector2{vectorLeft.getU() - vectorRight.getU(),
                       vectorLeft.getV() - vectorRight.getV()};
    }

    friend Vector2 operator*(const Vector2& vectorLeft, const Vector2& vectorRight) {
        return Vector2{vectorLeft.getU() * vectorRight.getU(),
                       vectorLeft.getV() * vectorRight.getV()};
    }

    friend Vector2 operator*(const double factor, const Vector2& vector) {
        return Vector2{factor * vector.getU(), factor * vector.getV()};
    }

    friend Vector2 operator*(const Vector2& vector, const double factor) {
        return factor * vector;
    }

    friend Vector2 operator/(const Vector2& vector, const double dividend) {
        return (1 / dividend) * vector;
    }
};

#endif //HAYA_LUZ_VECTOR2_H