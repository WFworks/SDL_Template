#pragma once

#include "Shape.h"
#include "RenderUtils.h"

class LineShape : public Shape
{
private:
    Vector2 mStartPos;
    Vector2 mEndPos;
    ColorCode mColor;

public:
    LineShape(class Application* a, bool b = true);
    ~LineShape();
    
    virtual void Update() override;
    virtual void Draw() override;
    

    void SetColor(const ColorCode c) { mColor = c; };
    void SetPosition(Vector2 s, Vector2 e) { mStartPos = s; mEndPos = e; };

};
