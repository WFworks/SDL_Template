#pragma once

#include "RenderUtils.h"
#include <SDL2/SDL.h>
#include <vector>



class Renderer
{
private:
    SDL_Window* mWin = nullptr;
    SDL_Renderer* mRend = nullptr;
    
    // 描画するシェイプを保持
    std::vector<class Shape*> mShapes;
    
public:
    Renderer(const char* title, const int scWidth, const int scHeight, bool bWindowed = true);
    ~Renderer();
    
    void Draw();
    
    
    void ClearScreen(ColorCode c);
    void DrawRectangle(int x, int y, int w, int h, ColorCode c);
    void FillRectangle(int x, int y, int w, int h, ColorCode c);
    void DrawLine(int sx, int sy, int ex, int ey, ColorCode c);
    void Present();
    
    void AddShape(class Shape* s);
    void RemoveShape(class Shape* s);
    
};
