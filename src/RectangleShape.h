#pragma once

#include "Shape.h"
#include "RenderUtils.h"

class RectangleShape : public Shape
{
private:
    Vector2 mPos;
    Vector2 mSize;
    ColorCode mColor;

public:
    RectangleShape(class Application* a, bool b = true);
    ~RectangleShape();
    
    virtual void Update() override;
    virtual void Draw() override;
    
    void SetSize(const Vector2 v) { mSize = v; }
    void SetPosition(const Vector2 v) { mPos = v; }
    void SetColor(const ColorCode c) { mColor = c; };

};
