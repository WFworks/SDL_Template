#include "Shape.h"
#include "Application.h"
#include "Renderer.h"

Shape::Shape(Application* a, bool b)
: mOwnerApp(a)
, mIsFilled(b)
{
    mOwnerApp->GetRenderer()->AddShape(this);
}

Shape::~Shape()
{
    mOwnerApp->GetRenderer()->RemoveShape(this);
}

// 派生先で実装する
void Shape::Update()
{
    
}

// まとめて呼び出し
void Shape::UpdateShape()
{
    Update();
}

// 派生先で実装する
void Shape::Draw()
{
    
}

// まとめて呼び出し
void Shape::DrawShape()
{
    Draw();
}
