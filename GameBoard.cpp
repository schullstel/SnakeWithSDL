#include "GameBoard.hpp"

#include "Tools/RandomNumberGenerator.hpp"

#include <iostream>

GameBoard::GameBoard() : m_food(new Food), m_score(0), m_elmosLength(0)
{
    std::cout << "GameBoard create" << std::endl;
    generateElmoInTheMiddleOfBoard();
    generateFoodInRandomPlace();
    std::cout << "GameBoard created" << std::endl;
}

GameBoard::~GameBoard()
{
    if (m_elmo != nullptr)
    {
        delete m_elmo;
    }
    if (m_food != nullptr)
    {
        delete m_food;
    }
}

void GameBoard::refreshBoard()
{
    bool elmoGrowUp = isFoodEaten();
    if (elmoGrowUp)
    {
        m_elmo->moveElmo(elmoGrowUp);
        generateFoodInRandomPlace();
        m_score += 10;
        m_elmosLength++;
    }
    else
    {
        m_elmo->moveElmo(elmoGrowUp);
    }
}

const Elmo *GameBoard::getElmo() const
{
    return m_elmo;
}

const Food *GameBoard::getFood() const
{
    return m_food;
}

void GameBoard::setElmosDirection(const Elmo::Direction newDirection)
{
    m_elmo->setDirection(newDirection);
}

Elmo::Direction GameBoard::getElmosDirection() const
{
    return m_elmo->getDirection();
}

uint32_t GameBoard::getScore() const
{
    return m_score;
}

uint32_t GameBoard::getElmosLength() const
{
    return m_elmosLength;
}

bool GameBoard::isElmoOutOfBounds() const
{
    const SDL_Point elmosHeadPosition = *(m_elmo->getHead());
    if (elmosHeadPosition.x < 0 || elmosHeadPosition.x > m_gameBoardWidht ||
        elmosHeadPosition.y < 0 || elmosHeadPosition.y > m_gameBoardHeight)
    {
        return true;
    }

    return false;
}

bool GameBoard::isElmoEatingItself() const
{
    return m_elmo->isElmoEatingItself();
}

uint16_t GameBoard::getGameBoardWidht()
{
    return m_gameBoardWidht;
}

uint16_t GameBoard::getGameBoardHeight()
{
    return m_gameBoardHeight;
}

void GameBoard::generateElmoInTheMiddleOfBoard()
{
    m_elmo = new Elmo(m_gameBoardWidht/2, m_gameBoardHeight/2, m_gameBoardWidht/2 + 1, m_gameBoardHeight/2);
    std::cout << "Elmo created, head on x=" << m_elmo->getHead()->x << " y=" << m_elmo->getHead()->y
              << " tail on x=" << m_elmo->getTail()->x << " y=" << m_elmo->getTail()->y << std::endl;
}

void GameBoard::generateFoodInRandomPlace()
{
    m_food->setFoodPosition(m_food->getRandomPostion(m_elmo->getElmosBody(), m_gameBoardWidht, m_gameBoardHeight));
    m_food->setFoodType(m_food->getRandomFoodType());

    std::cout << "Food created on x=" << m_food->getFoodPosition().x << " y=" << m_food->getFoodPosition().y << std::endl;
}

bool GameBoard::isFoodEaten() const
{
    const SDL_Point nextHeadPosition = m_elmo->getNextHeadPosition();
    const SDL_Point foodPosition = m_food->getFoodPosition();
    if (nextHeadPosition.x == foodPosition.x && nextHeadPosition.y == foodPosition.y)
    {
        return true;
    }
    return false;
}
