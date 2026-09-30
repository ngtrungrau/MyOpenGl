#include "Maths.h"
#include <cmath>
#include "Debug.h"
#include <iostream>
namespace MyGl
{
    // --- VEC2 ---
    Vec2::Vec2() : x(0), y(0) {}
    Vec2::Vec2(float x, float y) : x(x), y(y) {}

    Vec2 Vec2::operator+(const Vec2& other) const { return { x + other.x, y + other.y }; }
    Vec2 Vec2::operator-(const Vec2& other) const { return { x - other.x, y - other.y }; }

    Vec2& Vec2::operator+=(const Vec2& other) { x += other.x; y += other.y; return *this; }
    Vec2& Vec2::operator-=(const Vec2& other) { x -= other.x; y -= other.y; return *this; }

    float Vec2::Length() const { return std::sqrt(x * x + y * y); }

    Vec2& Vec2::Normalize()
    {
        float len = Length();
        if (len > 0.0f) { x /= len; y /= len; }
        else
        {
            ERROR_LOG("Lenght Vec2 = 0!!!");
        }
        return *this;
    }

    // --- VEC3 ---
    Vec3::Vec3() : x(0), y(0), z(0) {}
    Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3::Vec3(const float datas[3])
    {
        elements[0] = datas[0];
        elements[1] = datas[1];
        elements[2] = datas[2];
    }

    Vec3 Vec3::operator+(const Vec3& other) const { return { x + other.x, y + other.y, z + other.z }; }
    Vec3 Vec3::operator-(const Vec3& other) const { return { x - other.x, y - other.y, z - other.z }; }
    Vec3 Vec3::operator*(const float& other) const { return { x * other, y * other, z * other }; }

    Vec3& Vec3::operator+=(const Vec3& other) { x += other.x; y += other.y; z += other.z; return *this; }
    Vec3& Vec3::operator-=(const Vec3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }

    Vec3& Vec3::operator*=(const float& other)
    {
        x *= other; y *= other; z *= other;
        return *this;
    }

    float Vec3::Length() const { return std::sqrt(x * x + y * y + z * z); }

    Vec3& Vec3::Normalize()
    {
        float len = Length();
        if (len > 0.0f) { x /= len; y /= len; z /= len; }
        else
        {
            ERROR_LOG("Length Vec3 = 0!!!");
        }
        return *this;
    }

    
    float Vec3::Dot(const Vec3& v1, const Vec3& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    Vec3 Vec3::Cross(const Vec3& v1, const Vec3& v2)
    {
        return {
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        };
    }

    // --- VEC4 ---
    Vec4::Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Vec4::Vec4(const float datas[4]) {
        elements[0] = datas[0];
        elements[1] = datas[1];
        elements[2] = datas[2];
        elements[3] = datas[3];


    }
    Vec4 Vec4::operator+(const Vec4& other) const { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
    Vec4 Vec4::operator-(const Vec4& other) const { return { x - other.x, y - other.y, z - other.z, w - other.w }; }

    Vec4& Vec4::operator+=(const Vec4& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
    Vec4& Vec4::operator-=(const Vec4& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }

    // --- MAT4 ---
    Mat4::Mat4()
    {
        for (int i = 0; i < 16; ++i) Elements[i] = 0.0f;
    }


    Mat4& Mat4::Identity(float diagonal = 1.0f)
    {
        for (int i = 0; i < 16; ++i) Elements[i] = 0.0f;
        Columns[0].x = diagonal;
        Columns[1].y = diagonal;
        Columns[2].z = diagonal;
        Columns[3].w = diagonal;
        return *this;
    }

    Mat4 Mat4::operator*(const Mat4& other) const
    {
        Mat4 tmp;
        for (int i = 0; i < 4; i++)
        {
            tmp.Columns[i] = (*this) * other.Columns[i];
        }
        return tmp;
    }

    Vec4 Mat4::operator*(const Vec4& other) const
    {
        return Vec4(
            Columns[0].x * other.x + Columns[1].x * other.y + Columns[2].x * other.z + Columns[3].x * other.w,
            Columns[0].y * other.x + Columns[1].y * other.y + Columns[2].y * other.z + Columns[3].y * other.w,
            Columns[0].z * other.x + Columns[1].z * other.y + Columns[2].z * other.z + Columns[3].z * other.w,
            Columns[0].w * other.x + Columns[1].w * other.y + Columns[2].w * other.z + Columns[3].w * other.w
        );
    }
    Mat4& Mat4::Translate(const Vec3& translation)
    {
        Columns[3].x += translation.x;
        Columns[3].y += translation.y;
        Columns[3].z += translation.z;
        return *this;
    }
    Mat4& Mat4::Scale(const Vec3& scale)
    {
        Columns[0].x *= scale.x;
        Columns[1].y *= scale.y;
        Columns[2].z *= scale.z;
        return *this;
    }

    // Hàm Ortho hoàn chỉnh
    Mat4& Mat4::Ortho(float left, float right, float bottom, float top, float near, float far)
    {
        Identity(1.0f);

        float a = 2.0f / (right - left);
        float b = -(right + left) / (right - left); // Tương đương 1 - (2*right)/(right-left)

        float c = 2.0f / (top - bottom);
        float d = -(top + bottom) / (top - bottom);

        float e = -2.0f / (far - near);             // Đảo dấu âm cho OpenGL
        float f = -(far + near) / (far - near);

        Columns[0].x = a;
        Columns[1].y = c;
        Columns[2].z = e;
        Columns[3] = { b, d, f, 1.0f };

        return *this;
    }
}
