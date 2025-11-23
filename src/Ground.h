#pragma once
#include "Actor.h"
#include <memory>

class Ground : public Actor
{
private:

    std::unique_ptr<class RectangleShape> mShape;
    
public:
    Ground(class Application* a);
    ~Ground();
    void Update() override;

};
