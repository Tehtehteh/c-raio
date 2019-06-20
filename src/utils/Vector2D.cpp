#include "Vector2D.h"

Vector2D::Vector2D(GLfloat x, GLfloat y) : x(x), y(y){
}

Vector2D::~Vector2D() = default;

Vector2D Vector2D::operator+(const Vector2D& second) {
    return Vector2D(this->x + second.x, this->y + second.y);
}

Vector2D Vector2D::operator-(const Vector2D& second) {
    return Vector2D(this->x - second.x, this->y - second.y);
}

GLfloat Vector2D::operator*(const Vector2D& second) {
    return (this->x * second.x + this->y * second.y);
}

template<typename T>
Vector2D Vector2D::multiply(const T& t) {
    return Vector2D(this->x * t, this->y * t);
}

template<typename T>
Vector2D Vector2D::operator+(const T& second) {
    return Vector2D(this->x + second, this->y + second);
}

template<typename T>
Vector2D Vector2D::operator-(const T& second) {
    return Vector2D(this->x - second, this->y - second);
}

Vector2D Vector2D::operator-() {
    this->x = -this->x;
    this->y = -this->y;
    return *this;
}

GLfloat Vector2D::length() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

//std::ostream &Vector2D::operator<<(std::ostream& in, const Vector2D& vec) {
//    in << "Vector2D(x:" << vec.x << ", y:" << vec.y << ")";
//    return in;
//}
