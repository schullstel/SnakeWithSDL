#pragma once

#include "GameBoard.hpp"

#include <QDir>

#include <string>

namespace {
    constexpr static int WINDOW_WIDTH = 1024;
    constexpr static int WINDOW_HEIGHT = 800;
    constexpr static int BLOCK_WIDTH = 48;
    constexpr static int BLOCK_HEIGHT = 48;
    constexpr static int X_CORD_OFFSET = 240;
    constexpr static int Y_CORD_OFFSET = 16;
    constexpr static int DIGIT_WIDTH = 26;
    constexpr static int DIGIT_HEIGHT = 28;

    const static std::string headTexturePath = QDir::currentPath().toStdString() + "/Textures/head.bmp";
    const static std::string tailTexturePath = QDir::currentPath().toStdString() + "/Textures/tail.bmp";
    const static std::string straightTexturePath = QDir::currentPath().toStdString() + "/Textures/straight.bmp";
    const static std::string turnRightTexturePath = QDir::currentPath().toStdString() + "/Textures/turn1.bmp";
    const static std::string turnLeftTexturePath = QDir::currentPath().toStdString() + "/Textures/turn2.bmp";
    const static std::string backgroundPath = QDir::currentPath().toStdString() + "/Textures/background.bmp";
    const static std::string bananaTexturePath = QDir::currentPath().toStdString() + "/Textures/banana.bmp";
    const static std::string cheesecakeTexturePath = QDir::currentPath().toStdString() + "/Textures/cheesecake.bmp";
    const static std::string mochiTexturePath = QDir::currentPath().toStdString() + "/Textures/mochi.bmp";
    const static std::string sausageTexturePath = QDir::currentPath().toStdString() + "/Textures/sausage.bmp";
    const static std::string zeroTexturePath = QDir::currentPath().toStdString() + "/Textures/0.bmp";
    const static std::string oneTexturePath = QDir::currentPath().toStdString() + "/Textures/1.bmp";
    const static std::string twoTexturePath = QDir::currentPath().toStdString() + "/Textures/2.bmp";
    const static std::string threeTexturePath = QDir::currentPath().toStdString() + "/Textures/3.bmp";
    const static std::string fourTexturePath = QDir::currentPath().toStdString() + "/Textures/4.bmp";
    const static std::string fiveTexturePath = QDir::currentPath().toStdString() + "/Textures/5.bmp";
    const static std::string sixTexturePath = QDir::currentPath().toStdString() + "/Textures/6.bmp";
    const static std::string sevenTexturePath = QDir::currentPath().toStdString() + "/Textures/7.bmp";
    const static std::string eightTexturePath = QDir::currentPath().toStdString() + "/Textures/8.bmp";
    const static std::string nineTexturePath = QDir::currentPath().toStdString() + "/Textures/9.bmp";
    const static std::string scoreTexturePath = QDir::currentPath().toStdString() + "/Textures/score.bmp";
    const static std::string lengthTexturePath = QDir::currentPath().toStdString() + "/Textures/length.bmp";
    const static std::string wastedTexturePath = QDir::currentPath().toStdString() + "/Textures/wasted.bmp";
    const static std::string startTexturePath = QDir::currentPath().toStdString() + "/Textures/start.bmp";
    const static std::string pauseTexturePath = QDir::currentPath().toStdString() + "/Textures/pause.bmp";
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
    SDL_Texture* m_Zero;
    SDL_Texture* m_One;
    SDL_Texture* m_Two;
    SDL_Texture* m_Three;
    SDL_Texture* m_Four;
    SDL_Texture* m_Five;
    SDL_Texture* m_Six;
    SDL_Texture* m_Seven;
    SDL_Texture* m_Eight;
    SDL_Texture* m_Nine;
    SDL_Texture* m_ScoreText;
    SDL_Texture* m_LengthText;
    SDL_Texture* m_Wasted;
    SDL_Texture* m_StartScreen;
    SDL_Texture* m_Pause;

    bool m_Closed;
    uint32_t m_intervalMs;

    void drawGameBoard();
    void drawGameRectangle();
    void drawBackground();
    void drawFood();
    void drawElmo();
    void drawScore();
    void drawLength();
    void drawNumber(const int& x, const int& y, const uint32_t& number);
    void drawStartScreen();
    void drawGameOverScreen();
    void drawPauseScreen();

    void newGame();

    void handleKeyDownEvent(const SDL_KeyCode keyCode, bool canMoveInThisFrame);

    SDL_Texture* getFoodTexture(const Food::FoodType foodType) const;
    SDL_Texture* getSuitableTexture(const SDL_Point& previousPoint, const SDL_Point& currentPoint, const SDL_Point& nextPoint) const;
    SDL_Texture* getNumberTexture(const char& number) const;

    Rotation getSuitableHeadRotation() const;
    Rotation getSuitableTailRotation(const SDL_Point& tail, const SDL_Point& previousPoint) const;
    Rotation getSuitableTextureRotation(const SDL_Point& previousPoint, const SDL_Point& currentPoint, const SDL_Point& nextPoint) const;
};

