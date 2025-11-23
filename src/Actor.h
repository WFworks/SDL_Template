#pragma once

class Actor
{
public:
    Actor(class Application* a);
    virtual ~Actor();
    
    virtual void Update() = 0;
    void UpdateActor();
    
    float GetGroundLevel() const { return mGroundLevel; }
    void SetGroundLevel(const float f) { mGroundLevel = f; }
protected:
    float mGroundLevel;
    class Application* mOwnerApp;
};
