#include "Renderer.h"
#include "Shape.h"
#include <iostream>
#include <algorithm>


Renderer::Renderer(const char* title, const int scWidth, const int scHeight, bool bWindowed)
{
    // ウインドウ生成
    if (bWindowed)
    {
        mWin = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scWidth, scHeight, SDL_WINDOW_SHOWN);
    }
    else
    {
        mWin = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scWidth, scHeight, SDL_WINDOW_FULLSCREEN);
    }
    if(mWin == nullptr)
    {
        std::cerr << "Can not create window" << std::endl;
        return;
    }
    // レンダラー生成
    mRend = SDL_CreateRenderer(mWin, -1, SDL_RENDERER_ACCELERATED);
    if(mRend == nullptr)
    {
        std::cerr << "Can not create renderer" << std::endl;
        return;
    }
}


Renderer::~Renderer()
{
    mShapes.clear();
    
    // リリース処理
    if (mRend)
    {
        SDL_DestroyRenderer(mRend);
        mRend = nullptr;
    }
    if (mWin)
    {
        SDL_DestroyWindow(mWin);
        mWin = nullptr;
    }
}

void Renderer::Present()
{
    if (mRend)
    {
        SDL_RenderPresent(mRend);
    }
}

void Renderer::ClearScreen(ColorCode c)
{
    if (mRend)
    {
        SDL_SetRenderDrawColor(mRend, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(mRend);
    }
}

void Renderer::DrawRectangle(int x, int y, int w, int h, ColorCode c)
{
    if (mRend)
    {
        SDL_Rect rect = { x, y, w, h };
        SDL_SetRenderDrawColor(mRend, c.r, c.g, c.b, c.a);
        SDL_RenderDrawRect(mRend, &rect);
    }
}

void Renderer::FillRectangle(int x, int y, int w, int h, ColorCode c)
{
    if (mRend)
    {
        SDL_Rect rect = { x, y, w, h };
        SDL_SetRenderDrawColor(mRend, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(mRend, &rect);
    }
}

void Renderer::DrawLine(int sx, int sy, int ex, int ey, ColorCode c)
{
    if (mRend)
    {
        SDL_SetRenderDrawColor(mRend, c.r, c.g, c.b, c.a);
        SDL_RenderDrawLine(mRend, sx, sy, ex, ey);
    }
}

// シェイプのポインタを保持（所有権は持たない）
void Renderer::AddShape(Shape* s)
{
    mShapes.emplace_back(s);
}
void Renderer::RemoveShape(Shape* s)
{
    //mShapes.erase(std::remove(mShapes.begin(), mShapes.end(), s), mShapes.end());
    mShapes.erase(std::remove_if(mShapes.begin(), mShapes.end(),
        [](Shape* s) { return s == nullptr; }),
        mShapes.end());
}

void Renderer::Draw()
{
    
    // 背景クリア
    ClearScreen(ColorCode(0, 0, 127, 255));
    
    // nullptrチェック
    mShapes.erase(std::remove(mShapes.begin(), mShapes.end(), nullptr), mShapes.end());
    // シェイプを全て描画
    for (const auto& s : mShapes)
    {
        s->DrawShape();
    }
    
    
    // 画面表示
    Present();
    
    
}
