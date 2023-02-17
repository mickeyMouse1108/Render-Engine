﻿#pragma once

namespace Maths
{
    template <class T> struct Vec2;
    template <class T> struct Vec3;
    template <class T> struct Vec4;
    using Vector2 = Vec2<float>;
    using Vector3 = Vec3<float>;
    using Vector4 = Vec4<float>;
    using Vec2Int = Vec2<int>;
    using Vec3Int = Vec3<int>;
    using Vec4Int = Vec4<int>;

#pragma region Vec2 Declaration
    template <class T> struct Vec2
    {
        static const Vec2 RIGHT;
        static const Vec2 LEFT ;
        static const Vec2 UP   ;
        static const Vec2 DOWN ;
        static const Vec2 ZERO ;
        
        T x, y;
        Vec2() : x(0), y(0) {}
        Vec2(T x, T y = 0) : x(x), y(y) {}
        Vec2(T val) : x(val), y(val) {}
        Vec2(const Vec3<T>& vec3);

        template <class TOther> Vec2<TOther> Cast () { return {(TOther)x, (TOther)y}; }
                                Vector2      CastF() { return {(float) x, (float) y}; }

        T operator[] (unsigned int i) const { return ((const T*)this)[i]; }
        explicit operator T*() { return (T*)this; }
    };
    
    template <class T> Vec2<T> operator+ (const Vec2<T>& a, const Vec2<T>& b);
    template <class T> Vec2<T> operator- (const Vec2<T>& a, const Vec2<T>& b);
    template <class T> Vec2<T> operator* (const Vec2<T>& a, const Vec2<T>& b);
    template <class T> Vec2<T> operator/ (const Vec2<T>& a, const Vec2<T>& b);
    template <class T> Vec2<T> operator+ (const Vec2<T>& a, T b);
    template <class T> Vec2<T> operator- (const Vec2<T>& a, T b);
    template <class T> Vec2<T> operator* (const Vec2<T>& a, T b);
    template <class T> Vec2<T> operator/ (const Vec2<T>& a, T b);
#pragma endregion 

#pragma region Vec3 Declaration
    template <class T> struct Vec3
    {
        static const Vec3 RIGHT;
        static const Vec3 LEFT ;
        static const Vec3 UP   ;
        static const Vec3 DOWN ;
        static const Vec3 FRONT;
        static const Vec3 BACK ;
        static const Vec3 ZERO ;
        
        T x, y, z;
        Vec3() : x(0), y(0), z(0) {}
        Vec3(T x, T y, T z = 0) : x(x), y(y), z(z) {}
        Vec3(T val) : x(val), y(val), z(val) {}
        Vec3(const Vec2<T>& vec2, T z) : x(vec2.x), y(vec2.y), z(z) {}
        Vec3(const Vec3<T>& vec3) : x(vec3.x), y(vec3.y), z(vec3.z) {}
        Vec3(const Vec4<T>& vec4);

        template <class TOther> Vec3<TOther> Cast () { return {(TOther)x, (TOther)y, (TOther)z}; }
                                Vector3      CastF() { return {(float) x, (float) y, (float) z}; }

        T operator[] (unsigned int i) const { return ((const T*)this)[i]; }
        explicit operator T*() { return (T*)this; }
    };

    template <class T> Vec3<T> operator+ (const Vec3<T>& a, const Vec3<T>& b);
    template <class T> Vec3<T> operator- (const Vec3<T>& a, const Vec3<T>& b);
    template <class T> Vec3<T> operator* (const Vec3<T>& a, const Vec3<T>& b);
    template <class T> Vec3<T> operator/ (const Vec3<T>& a, const Vec3<T>& b);
    template <class T> Vec3<T> operator+ (const Vec3<T>& a, T b);
    template <class T> Vec3<T> operator- (const Vec3<T>& a, T b);
    template <class T> Vec3<T> operator* (const Vec3<T>& a, T b);
    template <class T> Vec3<T> operator/ (const Vec3<T>& a, T b);
#pragma endregion

#pragma region Vec4 Declaration
    template <class T> struct Vec4
    {
        static const Vec4 RIGHT;
        static const Vec4 LEFT ;
        static const Vec4 UP   ;
        static const Vec4 DOWN ;
        static const Vec4 FRONT;
        static const Vec4 BACK ;
        static const Vec4 IN   ;
        static const Vec4 OUT  ;
        static const Vec4 ZERO ;
        
        T x, y, z, w;
        Vec4() : x(0), y(0), z(0), w(0) {}
        Vec4(T x, T y, T z, T w = 0) : x(x), y(y), z(z), w(w) {}
        Vec4(T val) : x(val), y(val), z(val), w(val) {}
        Vec4(const Vec3<T>& vec3, T w = 0) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}

        template <class TOther> Vec4<TOther> Cast () { return {(TOther)x, (TOther)y, (TOther)z, (TOther)w}; }
                                Vector4      CastF() { return {(float) x, (float) y, (float) z, (float) w}; }

        T operator[] (unsigned int i) const { return ((const T*)this)[i]; }
        explicit operator T*() { return (T*)this; }
    };

    template <class T> Vec4<T> operator+ (const Vec4<T>& a, const Vec4<T>& b);
    template <class T> Vec4<T> operator- (const Vec4<T>& a, const Vec4<T>& b);
    template <class T> Vec4<T> operator* (const Vec4<T>& a, const Vec4<T>& b);
    template <class T> Vec4<T> operator/ (const Vec4<T>& a, const Vec4<T>& b);
    template <class T> Vec4<T> operator+ (const Vec4<T>& a, T b);
    template <class T> Vec4<T> operator- (const Vec4<T>& a, T b);
    template <class T> Vec4<T> operator* (const Vec4<T>& a, T b);
    template <class T> Vec4<T> operator/ (const Vec4<T>& a, T b);
#pragma endregion

#pragma region Vec2 Definition
    template <class T> Vec2<T> const Vec2<T>::RIGHT = {  1,  0 };
    template <class T> Vec2<T> const Vec2<T>::LEFT  = { -1,  0 };
    template <class T> Vec2<T> const Vec2<T>::UP    = {  0,  1 };
    template <class T> Vec2<T> const Vec2<T>::DOWN  = {  0, -1 };
    template <class T> Vec2<T> const Vec2<T>::ZERO  = {  0,  0 };
    
    template <class T> Vec2<T>::Vec2(const Vec3<T>& vec3) : x(vec3.x), y(vec3.y) {}

    template <class T> Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b) { return {a.x + b.x, a.y + b.y}; }
    template <class T> Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b) { return {a.x - b.x, a.y - b.y}; }
    template <class T> Vec2<T> operator*(const Vec2<T>& a, const Vec2<T>& b) { return {a.x * b.x, a.y * b.y}; }
    template <class T> Vec2<T> operator/(const Vec2<T>& a, const Vec2<T>& b) { return {a.x / b.x, a.y / b.y}; }
    template <class T> Vec2<T> operator+(const Vec2<T>& a, T b)              { return {a.x + b, a.y + b}; }
    template <class T> Vec2<T> operator-(const Vec2<T>& a, T b)              { return {a.x - b, a.y - b}; }
    template <class T> Vec2<T> operator*(const Vec2<T>& a, T b)              { return {a.x * b, a.y * b}; }
    template <class T> Vec2<T> operator/(const Vec2<T>& a, T b)              { return {a.x / b, a.y / b}; }
#pragma endregion

#pragma region Vec3 Definition
    template <class T> Vec3<T> const Vec3<T>::RIGHT = {  1,  0,  0 };
    template <class T> Vec3<T> const Vec3<T>::LEFT  = { -1,  0,  0 };
    template <class T> Vec3<T> const Vec3<T>::UP    = {  0,  1,  0 };
    template <class T> Vec3<T> const Vec3<T>::DOWN  = {  0, -1,  0 };
    template <class T> Vec3<T> const Vec3<T>::FRONT = {  0,  0,  1 };
    template <class T> Vec3<T> const Vec3<T>::BACK  = {  0,  0, -1 };
    template <class T> Vec3<T> const Vec3<T>::ZERO  = {  0,  0,  0 };
    
    template <class T> Vec3<T>::Vec3(const Vec4<T>& vec4) : x(vec4.x), y(vec4.y), z(vec4.z) {}

    template <class T> Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
    template <class T> Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
    template <class T> Vec3<T> operator*(const Vec3<T>& a, const Vec3<T>& b) { return {a.x * b.x, a.y * b.y, a.z * b.z}; }
    template <class T> Vec3<T> operator/(const Vec3<T>& a, const Vec3<T>& b) { return {a.x / b.x, a.y / b.y, a.z / b.z}; }
    template <class T> Vec3<T> operator+(const Vec3<T>& a, T b)              { return {a.x + b, a.y + b, a.z + b}; }
    template <class T> Vec3<T> operator-(const Vec3<T>& a, T b)              { return {a.x - b, a.y - b, a.z - b}; }
    template <class T> Vec3<T> operator*(const Vec3<T>& a, T b)              { return {a.x * b, a.y * b, a.z * b}; }
    template <class T> Vec3<T> operator/(const Vec3<T>& a, T b)              { return {a.x / b, a.y / b, a.z / b}; }
#pragma endregion

#pragma region Vec4 Definition
    template <class T> Vec4<T> const Vec4<T>::RIGHT = {  1,  0,  0,  0 };
    template <class T> Vec4<T> const Vec4<T>::LEFT  = { -1,  0,  0,  0 };
    template <class T> Vec4<T> const Vec4<T>::UP    = {  0,  1,  0,  0 };
    template <class T> Vec4<T> const Vec4<T>::DOWN  = {  0, -1,  0,  0 };
    template <class T> Vec4<T> const Vec4<T>::FRONT = {  0,  0,  1,  0 };
    template <class T> Vec4<T> const Vec4<T>::BACK  = {  0,  0, -1,  0 };
    template <class T> Vec4<T> const Vec4<T>::IN    = {  0,  0,  0,  1 };
    template <class T> Vec4<T> const Vec4<T>::OUT   = {  0,  0,  0, -1 };
    template <class T> Vec4<T> const Vec4<T>::ZERO  = {  0,  0,  0,  0 };
    
    template <class T> Vec4<T> operator+(const Vec4<T>& a, const Vec4<T>& b) { return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}; }
    template <class T> Vec4<T> operator-(const Vec4<T>& a, const Vec4<T>& b) { return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}; }
    template <class T> Vec4<T> operator*(const Vec4<T>& a, const Vec4<T>& b) { return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w}; }
    template <class T> Vec4<T> operator/(const Vec4<T>& a, const Vec4<T>& b) { return {a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w}; }
    template <class T> Vec4<T> operator+(const Vec4<T>& a, T b)              { return {a.x + b, a.y + b, a.z + b, a.w + b}; }
    template <class T> Vec4<T> operator-(const Vec4<T>& a, T b)              { return {a.x - b, a.y - b, a.z - b, a.w - b}; }
    template <class T> Vec4<T> operator*(const Vec4<T>& a, T b)              { return {a.x * b, a.y * b, a.z * b, a.w * b}; }
    template <class T> Vec4<T> operator/(const Vec4<T>& a, T b)              { return {a.x / b, a.y / b, a.z / b, a.w / b}; }
#pragma endregion
}