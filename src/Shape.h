#pragma once
#include "RenderUtils.h"

class Shape
{
public:
    Shape(class Application* a, bool b = true);
    virtual ~Shape();
    
    virtual void Update();
    void UpdateShape();
    virtual void Draw();
    void DrawShape();
    
protected:
    bool mIsFilled;
    class Application* mOwnerApp;
    
};
