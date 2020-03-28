#pragma once


template <typename T>
class Point {
public:
    Point() = default;

    Point(T x, T y);

    template <typename U>
    explicit Point(const Point<U>& p);

    T x() const;
    T y() const;

    void set_x(T x);
    void set_y(T y);

    void move_x(T dx);
    void move_y(T dy);

    void scale_x(T dx);
    void scale_y(T dy);

    Point<T> operator-() const;

    Point<T>& operator+=(const Point<T>& other);
    Point<T>& operator-=(const Point<T>& other);

    Point<T>& operator*=(T other);
    Point<T>& operator/=(T other);

    bool is_zero() const;

    T len2() const;
    T len() const;
    Point<T> norm() const;

private:
    T _x = 0;
    T _y = 0;
};

using PointF = Point<float>;
using PointI = Point<int>;

template <typename T>
bool operator==(const Point<T>& p1, const Point<T>& p2);

template <typename T>
inline bool operator!=(const Point<T>& p1, const Point<T>& p2) {
    return !(p1 == p2);
}

template <typename T>
Point<T> operator*(T other, Point<T> point);

template <typename T>
Point<T> operator*(const Point<T>& point, T other);

template <typename T>
Point<T> operator/(Point<T> point, T other);

template <typename T>
Point<T> operator+(Point<T> p1, const Point<T>& p2);

template <typename T>
Point<T> operator-(Point<T> p1, const Point<T>& p2);

template <typename T>
T dist2(const Point<T>& p1, const Point<T>& p2);

int grid_round(float n);

PointI grid_round(const PointF& p);
