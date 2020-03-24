#pragma once

class Point {
private:
    float _x = 0;
    float _y = 0;

public:
    Point() = default;

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

    Point& operator*=(float other) {
        scale_x(other);
        scale_y(other);
        return *this;
    }

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

