#include "PendulumActor.h"
#include "Application.h"
#include "LineShape.h"
#include "RectangleShape.h"
#include <cmath>

const float PI = 3.1415926535f;
const float GRAVITY = 9.81f;
const float SIZE = 8.f;

PendulumActor::PendulumActor(Application* a)
: Actor(a)
, mPivotPos(Vector2(0.f, 0.f))
, mWeightPos(Vector2(0.f, 0.f))
, mLength(100.f)
, mTheta(PI / 4.f)
, mOmega(0.f)
, mAlpha(0.f)
, mMass(1.f)
, mParent(nullptr)
, mChild(nullptr)
{
    mRope = std::make_unique<LineShape>(a, true);
    mWeight = std::make_unique<RectangleShape>(a, true);
    mWeight->SetPosition(Vector2(0.f, 0.f));
    mWeight->SetSize(Vector2(SIZE, SIZE));
    mWeight->SetColor(ColorCode(200, 0, 0, 255));

    mFootprintLines.resize(20);
    for (int i = 0; i < 20; i++)
    {
        mFootprintLines[i] = std::make_unique<LineShape>(a, true);
        mFootprintLines[i]->SetColor(ColorCode(255, 128, 255, 255));
    }
}

PendulumActor::~PendulumActor()
{
    
}

void PendulumActor::Update()
{
    
    // 物理計算
    // 振り子の動きを計算
    //float force = - (GRAVITY / mLength) * sin(mTheta);

    // 振り子の動きを計算(慣性を計算)
    float force = - (mMass * GRAVITY / mLength) * sin(mTheta);
    // 振り子の結合強度
    float coupling = 0.05f;
    // 粘性摩擦の減衰係数
    float dampingFactor = 0.02f;
    
    // 慣性モーメント
    //float I = mMass * mLength * mLength;
    // トルク（重力による影響）
    float torque = -mMass * GRAVITY * mLength * sin(mTheta);
    torque -= dampingFactor * mOmega;
    
    // 上の振り子の影響
    if (mParent != nullptr)
    {
        force -= coupling * (mTheta - mParent->GetTheta());

        // 親がある場合は振り子の視点を親のオモリの位置に調整
        mPivotPos.x = mParent->GetWeightPosition().x;
        mPivotPos.y = mParent->GetWeightPosition().y;
    }

    // 下の振り子からの影響
    if (mChild != nullptr)
    {
        force -= coupling * (mTheta - mChild->GetTheta());
    }
        
    //mAlpha = torque / I;
    mAlpha = force;
    // 角度を更新
    //　デルタタイムを0.4に決め打ちしている。画面のスケールに合わせて他のパラメータを調整して、0.016に合わせたいところ。
    mOmega += mAlpha * 0.4;
    mTheta += mOmega * 0.4;


    // 振り子の座標計算
    mWeightPos.x = mPivotPos.x + static_cast<int>(mLength * sin(mTheta));
    mWeightPos.y = mPivotPos.y + static_cast<int>(mLength * cos(mTheta));

    // 振り子のヒモの座標をセット
    mRope->SetPosition(mPivotPos, mWeightPos);
    // オモリの場所をセット
    mWeight->SetPosition(mWeightPos);

    // 軌跡を残す
    if (mFootprints.size() >= 20)
    {
        mFootprints.erase(mFootprints.begin());
    }
    mFootprints.push_back(mWeightPos);
    for (int i = 0; i < mFootprints.size()-1; i++)
    {
        mFootprintLines[i]->SetPosition(mFootprints[i], mFootprints[i+1]);
    }
    
    // オモリの描画サイズを質量に合わせる
    mWeight->SetSize(Vector2(SIZE*mMass, SIZE*mMass));
}


void PendulumActor::SetParent(class PendulumActor *p)
{
    mParent = p;
    if (p->GetChild() == nullptr)
    {
        // 親に子がセットされなかったら、自分を子に設定
        mParent->SetChild(this);
    }
}

void PendulumActor::SetChild(class PendulumActor *p)
{
    mChild = p;
    if (mChild->GetParent() == nullptr)
    {
        // 子に親がセットされてなかったら自分を親に設定
        mChild->SetParent(this);
    }
}
