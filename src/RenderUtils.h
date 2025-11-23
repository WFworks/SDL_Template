#pragma once


struct ColorCode
{
    ColorCode(const int R, const int G, const int B, const int A) : r(R), g(G), b(B), a(A) {}
    int r = 0;
    int g = 0;
    int b = 0;
    int a = 255;
};

struct Vector2
{
    Vector2(const float X, const float Y) : x(X), y(Y) {}
    float x = 0.f;
    float y = 0.f;
};
