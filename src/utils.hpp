#pragma once

#include "utils.h"

#include <cmath>

template <typename T>
Point<T>::Point(T x, T y) : _x(x), _y(y) {}

template<typename T>
template<typename U>
Point<T>::Point(const Point<U>& p) : Point(p.x(), p.y()) {
}

template <typename T>
T Point<T>::x() const { return _x; }

template <typename T>
T Point<T>::y() const { return _y; }

template <typename T>
void Point<T>::set_x(T x) { _x = x; }

template <typename T>
void Point<T>::set_y(T y) { _y = y; }

template <typename T>
void Point<T>::move_x(T dx) { _x += dx; }

template <typename T>
void Point<T>::move_y(T dy) { _y += dy; }

template <typename T>
void Point<T>::scale_x(T dx) { _x *= dx; }

template <typename T>
void Point<T>::scale_y(T dy) { _y *= dy; }

template <typename T>
Point<T> Point<T>::operator-() const {
    return {-_x, -_y};
}

template <typename T>
Point<T>& Point<T>::operator+=(const Point<T>& other) {
    move_x(other.x());
    move_y(other.y());
    return *this;
}

template <typename T>
Point<T>& Point<T>::operator-=(const Point<T>& other) {
    move_x(-other.x());
    move_y(-other.y());
    return *this;
}

template <typename T>
Point<T>& Point<T>::operator*=(T other) {
    scale_x(other);
    scale_y(other);
    return *this;
}

template <typename T>
Point<T>& Point<T>::operator/=(T other) {
    _x /= other;
    _y /= other;
    return *this;
}

template <typename T>
bool Point<T>::is_zero() const {
    return _x == 0 && _y == 0;
}

template <typename T>
T Point<T>::len2() const {
    return _x * _x + _y * _y;
}

template<typename T>
T Point<T>::len() const {
    return std::sqrt(len2());
}

template<typename T>
Point<T> Point<T>::norm() const {
    if (is_zero()) {
        return {0, 0};
    }
    return *this / len();
}

template <typename T>
bool operator==(const Point<T>& p1, const Point<T>& p2) {
    return p1.x() == p2.x() && p1.y() == p2.y();
}

template <typename T, typename U>
Point<T> operator*(U other, Point<T> point) {
    point *= other;
    return point;
}

template <typename T, typename U>
Point<T> operator*(const Point<T>& point, U other) {
    return other * point;
}

template <typename T, typename U>
Point<T> operator/(Point<T> point, U other) {
    point /= other;
    return point;
}

template <typename T>
Point<T> operator+(Point<T> p1, const Point<T>& p2) {
    p1 += p2;
    return p1;
}

template <typename T>
Point<T> operator-(Point<T> p1, const Point<T>& p2) {
    p1 -= p2;
    return p1;
}

template <typename T>
T dist2(const Point<T>& p1, const Point<T>& p2) {
    return (p1 - p2).len2();
}
