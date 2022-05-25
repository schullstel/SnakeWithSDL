#include "Drawer.hpp"

#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

Drawer::Drawer() : m_Window(nullptr), m_Renderer(nullptr)
                 , m_Background(nullptr), m_ElmoHead(nullptr)
                 , m_ElmoTail(nullptr), m_ElmoCorpsStraight(nullptr)
                 , m_ElmoTurnRight(nullptr), m_ElmoTurnLeft(nullptr)
                 , m_Closed(false), m_intervalMs(500)
{
}

Drawer::~Drawer()
{
    if (!m_Closed)
    {
        close();
    }
    delete m_gameBoard;
}

bool Drawer::initDrawer()
{
    m_gameBoard = new GameBoard();

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not be initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &m_Window, &m_Renderer);
    if (m_Window == nullptr || m_Renderer == nullptr)
    {
        std::cout << "Window or Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetWindowPosition(m_Window, 100, 100);
    SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
    SDL_SetWindowTitle(m_Window, "Elmo");

    return true;
}

bool Drawer::loadMedia()
{
    SDL_Surface* elmosHeadSurface = SDL_LoadBMP(headTexturePath.c_str());
    SDL_Surface* elmosTailSurface = SDL_LoadBMP(tailTexturePath.c_str());
    SDL_Surface* elmosStraightSurface = SDL_LoadBMP(straightTexturePath.c_str());
    SDL_Surface* elmosTurnVersion1Surface = SDL_LoadBMP(turnRightTexturePath.c_str());
    SDL_Surface* elmosTurnVersion2Surface = SDL_LoadBMP(turnLeftTexturePath.c_str());
    SDL_Surface* backgroundSurface = SDL_LoadBMP(backgroundPath.c_str());
    SDL_Surface* bananaSurface = SDL_LoadBMP(bananaTexturePath.c_str());
    SDL_Surface* cheesecakeSurface = SDL_LoadBMP(cheesecakeTexturePath.c_str());
    SDL_Surface* mochiSurface = SDL_LoadBMP(mochiTexturePath.c_str());
    SDL_Surface* sausageSurface = SDL_LoadBMP(sausageTexturePath.c_str());
    SDL_Surface* zeroSurface = SDL_LoadBMP(zeroTexturePath.c_str());
    SDL_Surface* oneSurface = SDL_LoadBMP(oneTexturePath.c_str());
    SDL_Surface* twoSurface = SDL_LoadBMP(twoTexturePath.c_str());
    SDL_Surface* threeSurface = SDL_LoadBMP(threeTexturePath.c_str());
    SDL_Surface* fourSurface = SDL_LoadBMP(fourTexturePath.c_str());
    SDL_Surface* fiveSurface = SDL_LoadBMP(fiveTexturePath.c_str());
    SDL_Surface* sixSurface = SDL_LoadBMP(sixTexturePath.c_str());
    SDL_Surface* sevenSurface = SDL_LoadBMP(sevenTexturePath.c_str());
    SDL_Surface* eightSurface = SDL_LoadBMP(eightTexturePath.c_str());
    SDL_Surface* nineSurface = SDL_LoadBMP(nineTexturePath.c_str());
    SDL_Surface* scoreSurface = SDL_LoadBMP(scoreTexturePath.c_str());
    SDL_Surface* lengthSurface = SDL_LoadBMP(lengthTexturePath.c_str());
    SDL_Surface* wastedSurface = SDL_LoadBMP(wastedTexturePath.c_str());
    SDL_Surface* startSurface = SDL_LoadBMP(startTexturePath.c_str());
    SDL_Surface* pauseSurface = SDL_LoadBMP(pauseTexturePath.c_str());


    m_ElmoHead = SDL_CreateTextureFromSurface(m_Renderer, elmosHeadSurface);
    m_ElmoTail = SDL_CreateTextureFromSurface(m_Renderer, elmosTailSurface);
    m_ElmoCorpsStraight = SDL_CreateTextureFromSurface(m_Renderer, elmosStraightSurface);
    m_ElmoTurnRight = SDL_CreateTextureFromSurface(m_Renderer, elmosTurnVersion1Surface);
    m_ElmoTurnLeft = SDL_CreateTextureFromSurface(m_Renderer, elmosTurnVersion2Surface);
    m_Background = SDL_CreateTextureFromSurface(m_Renderer, backgroundSurface);
    m_Banana = SDL_CreateTextureFromSurface(m_Renderer, bananaSurface);
    m_Cheesecake = SDL_CreateTextureFromSurface(m_Renderer, cheesecakeSurface);
    m_Mochi = SDL_CreateTextureFromSurface(m_Renderer, mochiSurface);
    m_Sausage = SDL_CreateTextureFromSurface(m_Renderer, sausageSurface);
    m_Zero = SDL_CreateTextureFromSurface(m_Renderer, zeroSurface);
    m_One = SDL_CreateTextureFromSurface(m_Renderer, oneSurface);
    m_Two = SDL_CreateTextureFromSurface(m_Renderer, twoSurface);
    m_Three = SDL_CreateTextureFromSurface(m_Renderer, threeSurface);
    m_Four = SDL_CreateTextureFromSurface(m_Renderer, fourSurface);
    m_Five = SDL_CreateTextureFromSurface(m_Renderer, fiveSurface);
    m_Six = SDL_CreateTextureFromSurface(m_Renderer, sixSurface);
    m_Seven = SDL_CreateTextureFromSurface(m_Renderer, sevenSurface);
    m_Eight = SDL_CreateTextureFromSurface(m_Renderer, eightSurface);
    m_Nine = SDL_CreateTextureFromSurface(m_Renderer, nineSurface);
    m_ScoreText = SDL_CreateTextureFromSurface(m_Renderer, scoreSurface);
    m_LengthText = SDL_CreateTextureFromSurface(m_Renderer, lengthSurface);
    m_Wasted = SDL_CreateTextureFromSurface(m_Renderer, wastedSurface);
    m_StartScreen = SDL_CreateTextureFromSurface(m_Renderer, startSurface);
    m_Pause = SDL_CreateTextureFromSurface(m_Renderer, pauseSurface);

    SDL_FreeSurface(elmosHeadSurface);
    SDL_FreeSurface(elmosTailSurface);
    SDL_FreeSurface(elmosStraightSurface);
    SDL_FreeSurface(elmosTurnVersion1Surface);
    SDL_FreeSurface(elmosTurnVersion2Surface);
    SDL_FreeSurface(backgroundSurface);
    SDL_FreeSurface(bananaSurface);
    SDL_FreeSurface(cheesecakeSurface);
    SDL_FreeSurface(mochiSurface);
    SDL_FreeSurface(sausageSurface);
    SDL_FreeSurface(zeroSurface);
    SDL_FreeSurface(oneSurface);
    SDL_FreeSurface(twoSurface);
    SDL_FreeSurface(threeSurface);
    SDL_FreeSurface(fourSurface);
    SDL_FreeSurface(fiveSurface);
    SDL_FreeSurface(sixSurface);
    SDL_FreeSurface(sevenSurface);
    SDL_FreeSurface(eightSurface);
    SDL_FreeSurface(nineSurface);
    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(lengthSurface);
    SDL_FreeSurface(wastedSurface);
    SDL_FreeSurface(startSurface);
    SDL_FreeSurface(pauseSurface);

    return true;
}

void Drawer::close()
{
    SDL_DestroyTexture(m_Background);
    SDL_DestroyTexture(m_ElmoHead);
    SDL_DestroyTexture(m_ElmoTail);
    SDL_DestroyTexture(m_ElmoCorpsStraight);
    SDL_DestroyTexture(m_ElmoTurnRight);
    SDL_DestroyTexture(m_ElmoTurnLeft);
    SDL_DestroyTexture(m_Banana);
    SDL_DestroyTexture(m_Cheesecake);
    SDL_DestroyTexture(m_Mochi);
    SDL_DestroyTexture(m_Sausage);
    SDL_DestroyTexture(m_Zero);
    SDL_DestroyTexture(m_One);
    SDL_DestroyTexture(m_Two);
    SDL_DestroyTexture(m_Three);
    SDL_DestroyTexture(m_Four);
    SDL_DestroyTexture(m_Five);
    SDL_DestroyTexture(m_Six);
    SDL_DestroyTexture(m_Seven);
    SDL_DestroyTexture(m_Eight);
    SDL_DestroyTexture(m_Nine);
    SDL_DestroyTexture(m_ScoreText);
    SDL_DestroyTexture(m_LengthText);
    SDL_DestroyTexture(m_Wasted);
    SDL_DestroyTexture(m_StartScreen);
    SDL_DestroyTexture(m_Pause);
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();

    m_Closed = true;
}

int Drawer::exec()
{
    using namespace std::chrono_literals;
    typedef std::chrono::high_resolution_clock Clock;

    uint32_t oldIntervalMs = m_intervalMs;
    bool initialFrameGenerated = false;
    bool paused = false;
    bool gameOver = false;
    bool startScreen = true;

    auto start = Clock::now();

    bool canMoveInThisFrame = true;
    for(auto done = false; !done;)
    {
        SDL_Event e;
        if(SDL_PollEvent(&e))
        {
            if ( e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    if (canMoveInThisFrame)
                    {
                        m_gameBoard->setElmosDirection(Elmo::Direction::Up);
                    }
                    canMoveInThisFrame = false;
                    break;
                case SDLK_DOWN:
                    if (canMoveInThisFrame)
                    {
                        m_gameBoard->setElmosDirection(Elmo::Direction::Down);
                    }
                    canMoveInThisFrame = false;
                    break;
                case SDLK_LEFT:
                    if (canMoveInThisFrame)
                    {
                        m_gameBoard->setElmosDirection(Elmo::Direction::Left);
                    }
                    canMoveInThisFrame = false;
                    break;
                case SDLK_RIGHT:
                    if (canMoveInThisFrame)
                    {
                        m_gameBoard->setElmosDirection(Elmo::Direction::Right);
                    }
                    canMoveInThisFrame = false;
                    break;
                case SDLK_SPACE:
                    m_intervalMs /= 2;
                    break;
                case SDLK_p:
                    if (!gameOver)
                    {
                        paused = !paused;
                        if (paused)
                        {
                            drawPauseScreen();
                            SDL_RenderPresent(m_Renderer);
                        }
                    }
                    break;
                case SDLK_r:
                    if (gameOver)
                    {
                        gameOver = false;
                        newGame();
                        SDL_RenderClear(m_Renderer);
                    }
                    break;
                case SDLK_s:
                    if (startScreen)
                    {
                        startScreen = false;
                    }
                    break;
                case SDLK_x:
                    if (gameOver || startScreen)
                    {
                        done = true;
                    }
                    break;
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_SPACE:
                    m_intervalMs = oldIntervalMs;
                    break;
                }
            }

            switch (e.type)
            {
            case SDL_QUIT:
                done = true;
                break;
            }
        }

        auto stop = Clock::now();

        if (!initialFrameGenerated)
        {
            initialFrameGenerated = true;
            SDL_RenderClear(m_Renderer);
            drawGameBoard();

            SDL_RenderPresent(m_Renderer);
        }

        if (startScreen)
        {
            SDL_RenderClear(m_Renderer);
            drawGameBoard();
            drawStartScreen();
            SDL_RenderPresent(m_Renderer);
        }

        if (!paused && !gameOver && !startScreen)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() >= m_intervalMs)
            {
                m_gameBoard->refreshBoard();
                if (m_gameBoard->isElmoOutOfBounds() || m_gameBoard->isElmoEatingItself())
                {
                    gameOver = true;
                    drawGameBoard();
                    drawGameOverScreen();
                    SDL_RenderPresent(m_Renderer);
                    continue;
                }

                start = Clock::now();
                canMoveInThisFrame = true;
                SDL_RenderClear(m_Renderer);
                drawGameBoard();

                SDL_RenderPresent(m_Renderer);
            }
        }

        std::this_thread::sleep_for(50ms);
    }
    return 0;
}

bool Drawer::tick()
{

}

void Drawer::drawGameBoard()
{
    drawBackground();
    drawGameRectangle();
    drawElmo();
    drawFood();
    drawScore();
    drawLength();
}

void Drawer::drawGameRectangle()
{
    SDL_Rect gameRectangle;
    gameRectangle.x = X_CORD_OFFSET;
    gameRectangle.y = Y_CORD_OFFSET;
    gameRectangle.h = (GameBoard::getGameBoardHeight() + 1) * BLOCK_HEIGHT;
    gameRectangle.w = (GameBoard::getGameBoardWidht() + 1) * BLOCK_WIDTH;

    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 100);
    SDL_RenderFillRect(m_Renderer, &gameRectangle);

    SDL_Rect outlineRectangle;
    outlineRectangle.x = gameRectangle.x - 1;
    outlineRectangle.y = gameRectangle.y - 1;
    outlineRectangle.h = gameRectangle.h + 2;
    outlineRectangle.w = gameRectangle.w + 2;
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(m_Renderer, &outlineRectangle);
}

void Drawer::drawBackground()
{
    SDL_Rect backgroundRect{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(m_Renderer, m_Background, &backgroundRect, &backgroundRect);
}

void Drawer::drawFood()
{
    const SDL_Point foodPosition = m_gameBoard->getFood()->getFoodPosition();
    const Food::FoodType foodType = m_gameBoard->getFood()->getFoodType();

    SDL_Rect foodRect{0, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
    SDL_Rect foodDestRect{(foodPosition.x * BLOCK_WIDTH) + X_CORD_OFFSET, (foodPosition.y * BLOCK_HEIGHT) + Y_CORD_OFFSET, BLOCK_WIDTH, BLOCK_HEIGHT};
    SDL_RenderCopy(m_Renderer, getFoodTexture(foodType), &foodRect, &foodDestRect);
}

void Drawer::drawElmo()
{
    const std::list<SDL_Point> elmoBody = m_gameBoard->getElmo()->getElmosBody();

    for (auto it = elmoBody.begin(); it != elmoBody.end(); it++)
    {
        const SDL_Point currentPoint = *it;
        bool isHead = false, isTail = false;

        SDL_Rect elmoRect{0, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
        SDL_Rect elmoDestRect{(currentPoint.x * BLOCK_WIDTH) + X_CORD_OFFSET, (currentPoint.y * BLOCK_HEIGHT) + Y_CORD_OFFSET, BLOCK_WIDTH, BLOCK_HEIGHT};

        const SDL_Point elmosHead = *(m_gameBoard->getElmo()->getHead());
        const SDL_Point elmosTail = *(m_gameBoard->getElmo()->getTail());

        if (Elmo::comparePoints(elmosHead, currentPoint))
        {
            Rotation elmosHeadRotation = getSuitableHeadRotation();
            SDL_RenderCopyEx(m_Renderer, m_ElmoHead, &elmoRect, &elmoDestRect, static_cast<double>(elmosHeadRotation), NULL, SDL_FLIP_NONE);
            isHead = true;
        }


        if (Elmo::comparePoints(elmosTail, currentPoint))
        {
            const auto previousPoint = *(std::prev(it));
            Rotation elmosTailRotation = getSuitableTailRotation(currentPoint, previousPoint);
            SDL_RenderCopyEx(m_Renderer, m_ElmoTail, &elmoRect, &elmoDestRect, static_cast<double>(elmosTailRotation), NULL, SDL_FLIP_NONE);
            isTail = true;
        }

        if (!(isHead) && !(isTail))
        {
            const auto previousPoint = *(std::prev(it));
            const auto nextPoint = *(std::next(it));
            Rotation elmosBodyPartRotation = getSuitableTextureRotation(previousPoint, currentPoint, nextPoint);
            SDL_RenderCopyEx(m_Renderer, getSuitableTexture(previousPoint, currentPoint, nextPoint), &elmoRect, &elmoDestRect, static_cast<double>(elmosBodyPartRotation), NULL, SDL_FLIP_NONE);
        }
    }
}

void Drawer::drawScore()
{
    SDL_Point scoreTextSize;
    SDL_QueryTexture(m_ScoreText, NULL, NULL, &scoreTextSize.x, &scoreTextSize.y);
    SDL_Rect scoreRect{0, 0, scoreTextSize.x, scoreTextSize.y};
    SDL_Rect scoreDestRect{50, 300, scoreTextSize.x, scoreTextSize.y};
    SDL_RenderCopy(m_Renderer, m_ScoreText, &scoreRect, &scoreDestRect);

    const uint32_t score = m_gameBoard->getScore();
    drawNumber(scoreTextSize.x + 25, 300 + scoreTextSize.y + 10, score);
}

void Drawer::drawLength()
{
    SDL_Point lengthTextSize;
    SDL_QueryTexture(m_LengthText, NULL, NULL, &lengthTextSize.x, &lengthTextSize.y);
    SDL_Rect lengthRect{0, 0, lengthTextSize.x, lengthTextSize.y};
    SDL_Rect lengthDestRect{25, 400, lengthTextSize.x, lengthTextSize.y};
    SDL_RenderCopy(m_Renderer, m_LengthText, &lengthRect, &lengthDestRect);

    const uint32_t length = m_gameBoard->getElmosLength();
    drawNumber(lengthTextSize.x - 33, 400 + lengthTextSize.y + 10, length);
}

void Drawer::drawNumber(const int& x, const int& y, const uint32_t& number)
{
    const std::string numberAsString = std::to_string(number);
    int digitsCount = numberAsString.size() - 1;

    for (const char& digit : numberAsString)
    {
        SDL_Texture* const digitTexture = getNumberTexture(digit);
        SDL_Point digitTextureSize;
        SDL_QueryTexture(digitTexture, NULL, NULL, &digitTextureSize.x, &digitTextureSize.y);
        SDL_Rect digitRect{0, 0, DIGIT_WIDTH, DIGIT_HEIGHT};
        SDL_Rect digitDestRect{x - (digitsCount * DIGIT_WIDTH), y, digitTextureSize.x, digitTextureSize.y};
        SDL_RenderCopy(m_Renderer, digitTexture, &digitRect, &digitDestRect);
        digitsCount--;
    }
}

void Drawer::drawStartScreen()
{
    SDL_Rect startRectangle;
    startRectangle.x = 0;
    startRectangle.y = 0;
    startRectangle.h = WINDOW_HEIGHT;
    startRectangle.w = WINDOW_WIDTH;
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 188);
    SDL_RenderFillRect(m_Renderer, &startRectangle);

    SDL_Point startTextureSize;
    SDL_QueryTexture(m_StartScreen, NULL, NULL, &startTextureSize.x, &startTextureSize.y);
    SDL_Rect startRect{0, 0, startTextureSize.x, startTextureSize.y};
    SDL_Rect startDestRect{(WINDOW_WIDTH / 2) - (startTextureSize.x /2), (WINDOW_HEIGHT / 2) - (startTextureSize.y / 2), startTextureSize.x, startTextureSize.y};
    SDL_RenderCopy(m_Renderer, m_StartScreen, &startRect, &startDestRect);
}

void Drawer::drawGameOverScreen()
{
    SDL_Rect gameOverRectangle;
    gameOverRectangle.x = 0;
    gameOverRectangle.y = 0;
    gameOverRectangle.h = WINDOW_HEIGHT;
    gameOverRectangle.w = WINDOW_WIDTH;
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 188);
    SDL_RenderFillRect(m_Renderer, &gameOverRectangle);

    SDL_Point wastedTextureSize;
    SDL_QueryTexture(m_Wasted, NULL, NULL, &wastedTextureSize.x, &wastedTextureSize.y);
    SDL_Rect wastedRect{0, 0, wastedTextureSize.x, wastedTextureSize.y};
    SDL_Rect wastedDestRect{(WINDOW_WIDTH / 2) - (wastedTextureSize.x /2), (WINDOW_HEIGHT / 2) - (wastedTextureSize.y / 2), wastedTextureSize.x, wastedTextureSize.y};
    SDL_RenderCopy(m_Renderer, m_Wasted, &wastedRect, &wastedDestRect);
}

void Drawer::drawPauseScreen()
{
    std::cout << "DrawPauseScreen" << std::endl;
    SDL_Rect pauseRectangle;
    pauseRectangle.x = 0;
    pauseRectangle.y = 0;
    pauseRectangle.h = WINDOW_HEIGHT;
    pauseRectangle.w = WINDOW_WIDTH;
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 188);
    SDL_RenderFillRect(m_Renderer, &pauseRectangle);

    SDL_Point pauseTextureSize;
    SDL_QueryTexture(m_Pause, NULL, NULL, &pauseTextureSize.x, &pauseTextureSize.y);
    SDL_Rect pauseRect{0, 0, pauseTextureSize.x, pauseTextureSize.y};
    SDL_Rect pauseDestRect{(WINDOW_WIDTH / 2) - (pauseTextureSize.x /2), (WINDOW_HEIGHT / 2) - (pauseTextureSize.y / 2), pauseTextureSize.x, pauseTextureSize.y};
    SDL_RenderCopy(m_Renderer, m_Pause, &pauseRect, &pauseDestRect);
}

void Drawer::newGame()
{
    if (m_gameBoard != nullptr)
    {
        delete m_gameBoard;
    }

    m_gameBoard = new GameBoard;
}

void Drawer::handleKeyDownEvent(const SDL_KeyCode keyCode, bool canMoveInThisFrame)
{

}

SDL_Texture* Drawer::getFoodTexture(const Food::FoodType foodType) const
{
    switch (foodType)
    {
    case Food::FoodType::Banana:
        return m_Banana;
    case Food::FoodType::Cheesecake:
        return m_Cheesecake;
    case Food::FoodType::Mochi:
        return m_Mochi;
    case Food::FoodType::Sausage:
        return m_Sausage;
    default:
        throw std::runtime_error("Unknown FoodType!");
    }
}

SDL_Texture* Drawer::getSuitableTexture(const SDL_Point& previousPoint, const SDL_Point& currentPoint, const SDL_Point& nextPoint) const
{
    if (previousPoint.y == currentPoint.y)
    {
        if ((currentPoint.x - previousPoint.x) > 0) // previous on left side
        {
            if ((currentPoint.y - nextPoint.y) > 0)
            {
                return m_ElmoTurnLeft; // turn left
            }
            else if ((currentPoint.y - nextPoint.y) < 0)
            {
                return m_ElmoTurnRight; // turn right
            }
        }
        else
        {
            if ((currentPoint.y - nextPoint.y) > 0)
            {
                return m_ElmoTurnRight; // turn right
            }
            else if ((currentPoint.y - nextPoint.y) < 0)
            {
                return m_ElmoTurnLeft; // turn left
            }
        }
    }

    if (previousPoint.x == currentPoint.x)
    {
        if ((currentPoint.y - previousPoint.y) > 0) // previous is upper
        {
            if ((currentPoint.x - nextPoint.x) > 0)
            {
                return m_ElmoTurnRight;
            }
            if ((currentPoint.x - nextPoint.x) < 0)
            {
                return m_ElmoTurnLeft;
            }
        }
        else
        {
            if ((currentPoint.x - nextPoint.x) > 0)
            {
                return m_ElmoTurnLeft;
            }
            if ((currentPoint.x - nextPoint.x) < 0)
            {
                return m_ElmoTurnRight;
            }
        }
    }
    return m_ElmoCorpsStraight;
}

SDL_Texture *Drawer::getNumberTexture(const char& number) const
{
    switch (number)
    {
    case '0':
        return m_Zero;
    case '1':
        return m_One;
    case '2':
        return m_Two;
    case '3':
        return m_Three;
    case '4':
        return m_Four;
    case '5':
        return m_Five;
    case '6':
        return m_Six;
    case '7':
        return m_Seven;
    case '8':
        return m_Eight;
    case '9':
        return m_Nine;
    default:
        throw std::runtime_error("Character is not one of numbers from 0 to 9");
    }
}

Drawer::Rotation Drawer::getSuitableHeadRotation() const
{
    const Elmo::Direction elmosDirection = m_gameBoard->getElmo()->getDirection();

    switch(elmosDirection)
    {
    case Elmo::Direction::Left:
        return Rotation::Rotate0Degrees;
    case Elmo::Direction::Right:
        return Rotation::Rotate180Degrees;
    case Elmo::Direction::Down:
        return Rotation::Rotate270Degrees;
    case Elmo::Direction::Up:
        return Rotation::Rotate90Degrees;
    case Elmo::Direction::Unknown:
        throw std::runtime_error("Unknown direction!");
    }
}

Drawer::Rotation Drawer::getSuitableTailRotation(const SDL_Point& tail, const SDL_Point& previousPoint) const
{
    if (tail.y == previousPoint.y)
    {
        if ((tail.x - previousPoint.x) > 0)
        {
            return Rotation::Rotate0Degrees;
        }
        else
        {
            return Rotation::Rotate180Degrees;
        }
    }
    else
    {
        if ((tail.y - previousPoint.y) > 0)
        {
            return Rotation::Rotate90Degrees;
        }
        else
        {
            return Rotation::Rotate270Degrees;
        }
    }
}

Drawer::Rotation Drawer::getSuitableTextureRotation(const SDL_Point& previousPoint, const SDL_Point& currentPoint, const SDL_Point& nextPoint) const
{
    if (previousPoint.y == currentPoint.y)
    {
        if ((currentPoint.x - previousPoint.x) > 0) // previous on left side
        {
            if ((currentPoint.y - nextPoint.y) > 0)
            {
                return Rotation::Rotate90Degrees;
            }
            else
            {
                return Rotation::Rotate0Degrees;
            }
        }
        else // previous is on right side
        {
            if ((currentPoint.y - nextPoint.y) < 0)
            {
                return Rotation::Rotate270Degrees;
            }
//            if ((currentPoint.y - nextPoint.y) > 0)
            else
            {
                return Rotation::Rotate180Degrees;
            }
        }
    }

    if (previousPoint.x == currentPoint.x)
    {
        if ((currentPoint.y - previousPoint.y) > 0) // previous is upper
        {
            if ((currentPoint.x - nextPoint.x) < 0)
            {
                return Rotation::Rotate180Degrees;
            }
            else
            {
                return Rotation::Rotate90Degrees;
            }
        }
        else // previous is lower
        {
            if ((currentPoint.x - nextPoint.x) > 0)
            {
                return Rotation::Rotate0Degrees;
            }
            else
            {
                return Rotation::Rotate270Degrees;
            }
        }
    }
}
