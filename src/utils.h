#pragma once

#include <cstdlib>
#include <cmath>

class Point {
public:
    Point() = default;

    static Point random() { return Point(rand(), rand()); }

    Point(float x, float y) : _x(x), _y(y) {}
    float x() const { return _x; }
    float y() const { return _y; }

    void set_x(float x) { _x = x; }
    void set_y(float y) { _y = y; }

    void move_x(float dx) { _x += dx; }
    void move_y(float dy) { _y += dy; }

    void scale_x(float dx) { _x *= dx; }
    void scale_y(float dy) { _y *= dy; }

    Point& operator+=(const Point& other) {
        move_x(other.x());
        move_y(other.y());
        return *this;
    }

    Point& operator-() {
        operator*=(-1);
        return *this;
    }

    Point& operator*=(float other) {
        scale_x(other);
        scale_y(other);
        return *this;
    }

    Point& operator-=(Point other) {
        operator+=(-other);
        return *this;
    }
    float dist2() {
        return _x * _x + _y* _y;
    }

private:
    float _x = 0;
    float _y = 0;
};

inline Point operator*(float other, Point point) {
    point *= other;
    return point;
}

inline Point operator*(const Point& point, float other) {
    return other * point;
}

inline Point operator+(Point p1, const Point& p2) {
    p1 += p2;
    return p1;
}

inline Point operator-(Point p1, const Point& p2) {
    p1 -= p2;
    return p1;
}

inline float dist2(const Point& p1, const Point& p2) {
    return (p1 - p2).dist2();
}

inline int grid_round(float n) {
    int dec = int(floorf(n * 10)) % 10;
    if (dec < 5) {
        return int(floorf(n));
    }
    return int(ceilf(n));
}
