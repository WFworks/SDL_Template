#include "Ground.h"
#include "RectangleShape.h"
#include "Application.h"
#include "Renderer.h"

Ground::Ground(Application* a)
: Actor(a)
{
    mShape = std::make_unique<RectangleShape>(a, true);
}

Ground::~Ground()
{
    
}

void Ground::Update()
{
    
    mShape->SetPosition(Vector2(mOwnerApp->GetScreenW() / 2,
                                mGroundLevel + (mOwnerApp->GetScreenH() - mGroundLevel) / 2)
                        );
    mShape->SetSize(Vector2(mOwnerApp->GetScreenW(),
                    mOwnerApp->GetScreenH() - (int)mGroundLevel));
    mShape->SetColor(ColorCode(128,128,128,255));
}
