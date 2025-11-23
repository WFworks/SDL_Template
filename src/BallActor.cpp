#include "BallActor.h"
#include "Application.h"
#include "RectangleShape.h"

const float SIZE = 20.f;

BallActor::BallActor(Application* a)
: Actor(a)
, mPos(Vector2(0.f, 0.f))
, mAccel(0.f)
, mSize(Vector2(SIZE, SIZE))
{
    mShape = std::make_unique<RectangleShape>(a, true);
    mShape->SetColor(ColorCode(200, 200, 0, 255));
}

BallActor::~BallActor()
{
    
}

void BallActor::Update()
{
   
    mAccel += 1.8f;
    mPos.y += mAccel;
    
    if(mPos.y > mGroundLevel - mSize.y/2)
    {
        mPos.y = mGroundLevel - mSize.y/2;
        mAccel = mAccel * -0.8f;
    }
    
    mShape->SetSize(mSize);
    mShape->SetPosition(mPos);
}
