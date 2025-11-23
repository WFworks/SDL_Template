#include "Actor.h"
#include "Application.h"

Actor::Actor(Application* a)
: mOwnerApp(a)
, mGroundLevel(0.f)
{
    mOwnerApp->AddActor(this);
}

Actor::~Actor()
{
    mOwnerApp->RemoveActor(this);
}

void Actor::Update()
{
    
}

void Actor::UpdateActor()
{
    Update();
}
