#pragma once
#include "Actor.h"
#include "RenderUtils.h"
#include <memory>

class BallActor : public Actor
{
private:
    Vector2 mPos;
    float mAccel;
    Vector2 mSize;
    std::unique_ptr<class RectangleShape> mShape;
public:
    BallActor(class Application* a);
    ~BallActor();
    virtual void Update() override;
    
    void SetSize(const Vector2 v) { mSize = v; };
    void SetPoisition(const Vector2 v) { mPos = v; }
};
