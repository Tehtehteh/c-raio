#ifndef GL_SKELETON_VECTOR2D_H
#define GL_SKELETON_VECTOR2D_H
#include <GLFW/glfw3.h>
#include <ostream>
#include <cmath>

class Vector2D {
public:
    Vector2D(GLfloat x, GLfloat y);
    ~Vector2D();
    friend std::ostream& operator<<(std::ostream& in, const Vector2D& vec) {
        in << "Vector2D(x:" << vec.x << ", y:" << vec.y << ")";
        return in;
    }
    Vector2D operator+(const Vector2D&);
    Vector2D operator-(const Vector2D&);
    Vector2D operator-();
    GLfloat operator*(const Vector2D&);
    GLfloat length();

    template<typename T>
    Vector2D operator+(const T&);
    template<typename T>
    Vector2D operator-(const T&);
    template<typename T>
    Vector2D multiply(const T&);

    GLfloat x;
    GLfloat y;
};


#endif
