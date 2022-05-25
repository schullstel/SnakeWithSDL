#include "Elmo.hpp"

#include <iostream>

Elmo::Elmo(const int32_t& xHead, const int32_t& yHead, const int32_t& xTail, const int32_t& yTail)
    : m_head(new SDL_Point({xHead, yHead})),
      m_tail(new SDL_Point({xTail, yTail})),
      m_direction(Direction::Left)
{
    m_blockAfterHead = m_tail;
    m_body.push_back(*m_head);
    m_body.push_back(*m_tail);
}

SDL_Point* Elmo::getHead()
{
    return m_head;
}

SDL_Point* Elmo::getTail()
{
    return m_tail;
}

SDL_Point* Elmo::getHead() const
{
    return m_head;
}

SDL_Point* Elmo::getTail() const
{
    return m_tail;
}

void Elmo::setDirection(const Direction newDirection)
{
    if ( (m_direction == Direction::Left && newDirection == Direction::Right) ||
         (m_direction == Direction::Right && newDirection == Direction::Left) ||
         (m_direction == Direction::Up && newDirection == Direction::Down) ||
         (m_direction == Direction::Down && newDirection == Direction::Up) )
    {
        return;
    }
    m_direction = newDirection;
}

Elmo::Direction Elmo::getDirection() const
{
    return m_direction;
}

std::list<SDL_Point> Elmo::getElmosBody() const
{
    return m_body;
}

SDL_Point Elmo::getNextHeadPosition()
{
    const Direction elmosDirection = getDirection();
    switch (elmosDirection)
    {
    case Direction::Up:
        return SDL_Point({m_head->x, m_head->y - 1});
    case Direction::Down:
        return SDL_Point({m_head->x, m_head->y + 1});
    case Direction::Left:
        return SDL_Point({m_head->x - 1, m_head->y});
    case Direction::Right:
        return SDL_Point({m_head->x + 1, m_head->y});
    default:
        throw std::runtime_error("Unknown Direction");
    }
}

void Elmo::moveElmo(const bool isFoodEaten)
{
    moveHead();

    if(!isFoodEaten)
    {
        moveTail();
    }
}

bool Elmo::isElmoEatingItself() const
{
    for (auto i = std::next(m_body.begin()); i != m_body.end(); i++)
    {
        if (comparePoints(*m_head, *i))
        {
            return true;
        }
    }

    return false;
}

bool Elmo::comparePoints(const SDL_Point &firstPoint, const SDL_Point &secondPoint)
{
    return (firstPoint.x == secondPoint.x && firstPoint.y == secondPoint.y);
}

Elmo::Direction Elmo::getElmoDirection() const
{
    if(m_head->y == m_blockAfterHead->y)
    {
        if(m_head->x > m_blockAfterHead->x)
        {
            return Direction::Right;
        }
        if(m_head->x < m_blockAfterHead->x)
        {
            return Direction::Left;
        }
    }

    if(m_head->x == m_blockAfterHead->x)
    {
        if(m_head->y > m_blockAfterHead->y)
        {
            return Direction::Up;
        }
        if(m_head->y < m_blockAfterHead->y)
        {
            return Direction::Down;
        }
    }
    std::cout << "Unknown direction. Should not happen" << std::endl;
    return Direction::Unknown;
}

void Elmo::moveHead()
{
    SDL_Point newHead = getNextHeadPosition();
    m_body.emplace_front(newHead);
    m_head = &(m_body.front());
}

void Elmo::moveTail()
{
    m_body.pop_back();
    m_tail = &(m_body.back());
}

