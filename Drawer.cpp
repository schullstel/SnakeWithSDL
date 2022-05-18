#include "Drawer.hpp"

#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

#include <SDL_image.h>


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

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_SetWindowPosition(m_Window, 100, 100);
    SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
    SDL_SetWindowTitle(m_Window, "Elmo");

    m_ScreenSurface = SDL_GetWindowSurface(m_Window);

    return true;
}

bool Drawer::loadMedia()
{
    SDL_Surface* elmosHeadSurface = loadSurface(headTexturePath);
    SDL_Surface* elmosTailSurface = loadSurface(tailTexturePath);
    SDL_Surface* elmosStraightSurface = loadSurface(straightTexturePath);
    SDL_Surface* elmosTurnVersion1Surface = loadSurface(turnRightTexturePath);
    SDL_Surface* elmosTurnVersion2Surface = loadSurface(turnLeftTexturePath);
    SDL_Surface* backgroundSurface = loadSurface(backgroundPath);
    SDL_Surface* bananaSurface = loadSurface(bananaTexturePath);
    SDL_Surface* cheesecakeSurface = loadSurface(cheesecakeTexturePath);
    SDL_Surface* mochiSurface = loadSurface(mochiTexturePath);
    SDL_Surface* sausageSurface = loadSurface(sausageTexturePath);
    Uint32 colorKey = SDL_MapRGB(sausageSurface->format, 0, 0, 0);
    SDL_SetColorKey(sausageSurface, SDL_TRUE, colorKey);

    Uint32 colorKey1 = SDL_MapRGB(mochiSurface->format, 0, 0, 0);
    SDL_SetColorKey(mochiSurface, SDL_TRUE, colorKey1);

    Uint32 colorKey2 = SDL_MapRGB(cheesecakeSurface->format, 0, 0, 0);
    SDL_SetColorKey(cheesecakeSurface, SDL_TRUE, colorKey2);

    Uint32 colorKey3 = SDL_MapRGB(bananaSurface->format, 0, 0, 0);
    SDL_SetColorKey(bananaSurface, SDL_TRUE, colorKey3);

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
    SDL_FreeSurface(m_ScreenSurface);
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
            case SDL_MOUSEBUTTONDOWN:
                std::cout << "CLICK " << e.button.x << " " << e.button.y << std::endl;
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_MOUSEBUTTONUP:
                std::cout << "RELEASE " <<  e.button.x << " " << e.button.y << std::endl;
                break;
            case SDL_QUIT:
                done = true;
                break;
            }
        }

        auto stop = Clock::now();

        if (std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() >= m_intervalMs)
        {
            m_gameBoard->refreshBoard();
            if (m_gameBoard->isElmoOutOfBounds())
            {
                done = true;
                continue;
            }
            start = Clock::now();
            canMoveInThisFrame = true;
            SDL_RenderClear(m_Renderer);
            drawGameBoard();

            SDL_RenderPresent(m_Renderer);
        }

//        SDL_RenderClear(m_Renderer);
//        drawGameBoard();

//        SDL_RenderPresent(m_Renderer);
        std::this_thread::sleep_for(100ms);
    }
    return 0;
}

bool Drawer::tick()
{

}

SDL_Surface* Drawer::loadSurface(const std::string& path)
{
    SDL_Surface* optimizedSurface = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    optimizedSurface = SDL_ConvertSurface( loadedSurface, m_ScreenSurface->format, 0);
    if (optimizedSurface == nullptr)
    {
        std::cout << "Unable to optimize image " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_FreeSurface(loadedSurface);

    Uint32 colorKey = SDL_MapRGB(optimizedSurface->format, 0, 0, 0);
    SDL_SetColorKey(optimizedSurface, SDL_TRUE, colorKey);

    return optimizedSurface;
}

void Drawer::drawGameBoard()
{
    SDL_Rect backgroundRect{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_RenderCopy(m_Renderer, m_Background, &backgroundRect, &backgroundRect);

    const std::list<SDL_Point> elmoBody = m_gameBoard->getElmo()->getElmosBody();
    const SDL_Point foodPosition = m_gameBoard->getFood()->getFoodPosition();
    const Food::FoodType foodType = m_gameBoard->getFood()->getFoodType();

    for (auto it = elmoBody.begin(); it != elmoBody.end(); it++)
    {
        const SDL_Point currentPoint = *it;
        bool isHead = false, isTail = false;

        SDL_Rect elmoRect{0, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
        SDL_Rect elmoDestRect{currentPoint.x * BLOCK_WIDTH, currentPoint.y * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT};

        const SDL_Point elmosHead = *(m_gameBoard->getElmo()->getHead());
        const SDL_Point elmosTail = *(m_gameBoard->getElmo()->getTail());

        if (comparePoints(elmosHead, currentPoint))
        {
            Rotation elmosHeadRotation = getSuitableHeadRotation(currentPoint);
            SDL_RenderCopyEx(m_Renderer, m_ElmoHead, &elmoRect, &elmoDestRect, static_cast<double>(elmosHeadRotation), NULL, SDL_FLIP_NONE);
            isHead = true;
        }


        if (comparePoints(elmosTail, currentPoint))
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

    SDL_Rect foodRect{0, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
    SDL_Rect foodDestRect{foodPosition.x * BLOCK_WIDTH, foodPosition.y * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT};
    SDL_RenderCopy(m_Renderer, getFoodTexture(foodType), &foodRect, &foodDestRect);
}

bool Drawer::comparePoints(const SDL_Point& firstPoint, const SDL_Point& secondPoint) const
{
    return (firstPoint.x == secondPoint.x && firstPoint.y == secondPoint.y);
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

Drawer::Rotation Drawer::getSuitableHeadRotation(const SDL_Point &head) const
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
            else  //if ((currentPoint.x - nextPoint.x) > 0)
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
            else  //if ((currentPoint.x - nextPoint.x) < 0)
            {
                return Rotation::Rotate270Degrees;
            }
        }
    }
}
