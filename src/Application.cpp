#include "Application.h"
#include "Renderer.h"
#include "RenderUtils.h"
#include "Actor.h"
#include "Ground.h"
#include "BallActor.h"
#include "PendulumActor.h"
#include <iostream>
#include <algorithm>

const char* TITLE = "Gravity";

const int SCREEN_H  = 720;
const int SCREEN_W  = 1280;

const float GROUND_LEVEL = 600.f;

// 初期化
Application::Application()
: mActive(true)
, mLoopCount(0)
, mTicksCount(0)
, mScreenH(SCREEN_H)
, mScreenW(SCREEN_W)
, mFps(0)
, mFpsCnt(0)
, mTicks(0)

{
    // SDL初期化
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL_Init(): " << SDL_GetError() << std::endl;
    }
        
    mRenderer = std::make_unique<Renderer>(TITLE, SCREEN_W, SCREEN_H, true);
    
    
    mGround = std::make_unique<Ground>(this);
    mGround->SetGroundLevel(GROUND_LEVEL);
    
    mBall = std::make_unique<BallActor>(this);
    mBall->SetPoisition(Vector2(SCREEN_W/4*3, 0));
    mBall->SetGroundLevel(GROUND_LEVEL);


    mBall2 = std::make_unique<BallActor>(this);
    mBall2->SetPoisition(Vector2(SCREEN_W/2, 100));
    mBall2->SetGroundLevel(GROUND_LEVEL);

    
    mBall3 = std::make_unique<BallActor>(this);
    mBall3->SetPoisition(Vector2(SCREEN_W/4, 300));
    mBall3->SetGroundLevel(GROUND_LEVEL);
    
    
    // 振り子を生成
    mPendulum1 = std::make_unique<PendulumActor>(this);
    mPendulum1->SetGroundLevel(GROUND_LEVEL);
    mPendulum1->SetPivotPosition(Vector2(SCREEN_W /4 , 300));
    mPendulum1->SetMass(1.0f);

    mPendulum2 = std::make_unique<PendulumActor>(this);
    mPendulum2->SetGroundLevel(GROUND_LEVEL);
    mPendulum2->SetParent(mPendulum1.get());
    mPendulum2->SetMass(2.f);

    mPendulum3 = std::make_unique<PendulumActor>(this);
    mPendulum3->SetGroundLevel(GROUND_LEVEL);
    mPendulum3->SetParent(mPendulum2.get());
    mPendulum3->SetMass(3.f);
    
    
    mPendulum4 = std::make_unique<PendulumActor>(this);
    mPendulum4->SetGroundLevel(GROUND_LEVEL);
    mPendulum4->SetPivotPosition(Vector2(SCREEN_W /4*3 , 300));
    mPendulum4->SetMass(3.0f);

    mPendulum5 = std::make_unique<PendulumActor>(this);
    mPendulum5->SetGroundLevel(GROUND_LEVEL);
    mPendulum5->SetParent(mPendulum4.get());
    mPendulum5->SetMass(2.f);

    mPendulum6 = std::make_unique<PendulumActor>(this);
    mPendulum6->SetGroundLevel(GROUND_LEVEL);
    mPendulum6->SetParent(mPendulum5.get());
    mPendulum6->SetMass(1.f);
}


// デストラクタ
Application::~Application()
{
    mActors.clear();
    SDL_Quit();
}

void Application::Update()
{
    mLoopCount++;
    if (mLoopCount % 5 != 0)
    {
        return;
    }
    
    for (auto a : mActors)
    {
        a->UpdateActor();
    }

}

// 描画
void Application::Draw()
{
    // FPS60固定
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
    {
        SDL_Delay(1);
    }
    mTicksCount = SDL_GetTicks();
    
    mRenderer->Draw();
    
    mFpsCnt++;
    if (mTicks + 1000 < SDL_GetTicks())
    {
        mTicks = SDL_GetTicks();
        mFps = mFpsCnt;
        mFpsCnt = 0;
    }
    std::cout << mFps << std::endl;
    
    
}


void Application::Execute()
{
    // メインループ
    while(mActive)
    {
        Update();
        // 画面描画
        Draw();
                
        // アプリ終了条件
        while(SDL_PollEvent(&mEvent))
        {
            switch(mEvent.type)
            {
                case SDL_KEYDOWN:
                    switch(mEvent.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            mActive = false;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    mActive = false;
                    break;
                default:
                    break;
            }
        }
    }
}


void Application::AddActor(Actor* a)
{
    mActors.push_back(a);
}

void Application::RemoveActor(Actor *a)
{  
    //mActors.erase(std::remove(mActors.begin(), mActors.end(), a), mActors.end());
    mActors.erase(std::remove_if(mActors.begin(), mActors.end(),
        [a](Actor* actor) { return actor == a; }),
        mActors.end());
}
