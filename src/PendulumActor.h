#pragma once
#include "Actor.h"
#include "RenderUtils.h"
#include <memory>
#include <vector>

class PendulumActor : public Actor
{
private:
    Vector2 mPivotPos;
    Vector2 mWeightPos;

    std::unique_ptr<class LineShape> mRope;
    std::unique_ptr<class RectangleShape> mWeight;
    
    // 振り子のパラメータ
    float mLength;  // 長さ
    float mTheta;   // 初期角度
    float mOmega;   // 角速度
    float mAlpha;   // 角加速度
    float mMass;    // 質量
    
    class PendulumActor* mParent; // 親のポインタ
    class PendulumActor* mChild;  // 子のポインタ
    
    std::vector<Vector2> mFootprints;
    std::vector<std::unique_ptr<class LineShape>> mFootprintLines;

    
public:
    PendulumActor(class Application* a);
    ~PendulumActor();
    
    virtual void Update() override;
    
    // Getter/Setter
    void SetPivotPosition(const Vector2 v) { mPivotPos = v; }
    void SetLength(const float f) { mLength = f; }
    
    void SetParent(class PendulumActor* p);
    PendulumActor* GetParent() const { return mParent; }
    void SetChild(class PendulumActor* p);
    PendulumActor* GetChild() const { return mChild; }
    
    float GetTheta() const { return mTheta; }
    Vector2 GetWeightPosition() const { return mWeightPos; }
    Vector2 GetPivotPosition() const { return mPivotPos; }
    
    float GetMass() const { return mMass; }
    void SetMass(const float f) { mMass = f; }
};
