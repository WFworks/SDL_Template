#include "RectangleShape.h"
#include "Application.h"
#include "Renderer.h"


RectangleShape::RectangleShape(Application* a, bool b)
: Shape(a, b)
, mPos(Vector2(0.f, 0.f))
, mSize(Vector2(0.f, 0.f))
, mColor(ColorCode(255, 255, 255, 255))
{

}

RectangleShape::~RectangleShape()
{
    
}

void RectangleShape::Update()
{
    
}

void RectangleShape::Draw()
{
    // 塗りつぶしありの場合
    if (mIsFilled)
    {
        mOwnerApp->GetRenderer()->FillRectangle(mPos.x - (mSize.x/2), mPos.y - (mSize.y/2), mSize.x, mSize.y, mColor);
    }
    // 塗りつぶしなしの場合
    else
    {
        mOwnerApp->GetRenderer()->DrawRectangle(mPos.x - (mSize.x/2), mPos.y - (mSize.y/2), mSize.x, mSize.y, mColor);
    }
}
