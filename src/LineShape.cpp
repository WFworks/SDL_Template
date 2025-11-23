#include "LineShape.h"
#include "Application.h"
#include "Renderer.h"


LineShape::LineShape(Application* a, bool b)
: Shape(a, b)
, mStartPos(Vector2(0.f, 0.f))
, mEndPos(Vector2(0.f, 0.f))
, mColor(ColorCode(255, 255, 255, 255))
{

}

LineShape::~LineShape()
{
    
}

void LineShape::Update()
{
    
}

void LineShape::Draw()
{
    mOwnerApp->GetRenderer()->DrawLine(mStartPos.x, mStartPos.y, mEndPos.x, mEndPos.y, mColor);
}

