#pragma once

#include "GameBoard.hpp"

#include <string>

namespace {
    constexpr static int WINDOW_WIDTH = 1024;
    constexpr static int WINDOW_HEIGHT = 768;
    constexpr static int BLOCK_WIDTH = 48;
    constexpr static int BLOCK_HEIGHT = 48;

    const static std::string headTexturePath = "F:/Programowanie/Elmo/Elmo/Textures/head.png";
    const static std::string tailTexturePath = "F:/Programowanie/Elmo/Elmo/Textures/tail.png";
    const static std::string straightTexturePath = "F:/Programowanie/Elmo/Elmo/Textures/straight.png";
    const static std::string turnRightTexturePath = "F:/Programowanie/Elmo/Elmo/Textures/turn1.png";
    const static std::string turnLeftTexturePath = "F:/Programowanie/Elmo/Elmo/Textures/turn2.png";
    const static std::string backgroundPath = "F:/Programowanie/Elmo/Elmo/Textures/background.png";
    const static std::string bananaTexturePath = "F:/Programowanie/Elmo/Elmo/Textures/banana.png";
    const static std::string cheesecakeTexturePath = "F:/Programowanie/Elmo/Elmo/Textures/cheesecake.png";
    const static std::string mochiTexturePath = "F:/Programowanie/Elmo/Elmo/Textures/mochi.png";
    const static std::string sausageTexturePath = "F:/Programowanie/Elmo/Elmo/Textures/sausage.png";
}

class Drawer
{
public:
    enum class Rotation
    {
        Rotate0Degrees = 0,
        Rotate90Degrees = 90,
        Rotate180Degrees = 180,
        Rotate270Degrees = 270
    };

    Drawer();
    ~Drawer();
    bool initDrawer();
    bool loadMedia();
    void close();
    int exec();
    bool tick();

private:
    GameBoard* m_gameBoard;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Texture* m_Background;
    SDL_Texture* m_ElmoHead;
    SDL_Texture* m_ElmoTail;
    SDL_Texture* m_ElmoCorpsStraight;
    SDL_Texture* m_ElmoTurnRight;
    SDL_Texture* m_ElmoTurnLeft;
    SDL_Texture* m_Banana;
    SDL_Texture* m_Cheesecake;
    SDL_Texture* m_Mochi;
    SDL_Texture* m_Sausage;
    SDL_Surface* m_ScreenSurface;
    bool m_Closed;
    uint32_t m_intervalMs;

    SDL_Surface* loadSurface(const std::string& path);
    void drawGameBoard();
    bool comparePoints(const SDL_Point& firstPoint, const SDL_Point& secondPoint) const;

    void handleKeyDownEvent(const SDL_KeyCode keyCode, bool canMoveInThisFrame);

    SDL_Texture* getFoodTexture(const Food::FoodType foodType) const;
    SDL_Texture* getSuitableTexture(const SDL_Point& previousPoint, const SDL_Point& currentPoint, const SDL_Point& nextPoint) const;

    Rotation getSuitableHeadRotation(const SDL_Point& head) const;
    Rotation getSuitableTailRotation(const SDL_Point& tail, const SDL_Point& previousPoint) const;
    Rotation getSuitableTextureRotation(const SDL_Point& previousPoint, const SDL_Point& currentPoint, const SDL_Point& nextPoint) const;
};

