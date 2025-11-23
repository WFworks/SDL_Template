#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <memory>

class Application
{
private:
    
    SDL_Event mEvent;
    bool mActive;
    unsigned int mLoopCount;
    unsigned int mTicksCount;
    
    std::unique_ptr<class Renderer> mRenderer;
    std::vector<class Actor*> mActors;
    

    // 描画
    void Draw();
    void Update();
    
    int mScreenH;
    int mScreenW;

    std::unique_ptr<class Ground> mGround;
    std::unique_ptr<class BallActor> mBall;
    std::unique_ptr<class BallActor> mBall2;
    std::unique_ptr<class BallActor> mBall3;
    std::unique_ptr<class PendulumActor> mPendulum1;
    std::unique_ptr<class PendulumActor> mPendulum2;
    std::unique_ptr<class PendulumActor> mPendulum3;
    std::unique_ptr<class PendulumActor> mPendulum4;
    std::unique_ptr<class PendulumActor> mPendulum5;
    std::unique_ptr<class PendulumActor> mPendulum6;
    
    unsigned int mFps;
    unsigned int mFpsCnt;
    unsigned int mTicks;
    
public:
    // コンストラクタ、デストラクタ
    Application();
    ~Application();
    
    void AddActor(class Actor* a);
    void RemoveActor(class Actor* a);

    class Renderer* GetRenderer() const { return mRenderer.get(); }
    // メインルーチン
    void Execute();
    
    int GetScreenH() const { return mScreenH; }
    int GetScreenW() const { return mScreenW; }
};
