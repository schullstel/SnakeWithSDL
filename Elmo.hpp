#pragma once

#include <stdint.h>
#include <list>

#include <SDL.h>

class Elmo
{
public:
    enum class Direction
    {
        Left = 0,
        Right,
        Up,
        Down,
        Unknown
    };

    Elmo() = delete;
    Elmo(const int32_t& xHead, const int32_t& yHead, const int32_t& xTail, const int32_t& yTail);
    ~Elmo() = default;

    SDL_Point* getHead();
    SDL_Point* getTail();
    SDL_Point* getHead() const;
    SDL_Point* getTail() const;

    void setDirection(const Direction newDirection);
    Direction getDirection() const;

    std::list<SDL_Point> getElmosBody() const;

    SDL_Point getNextHeadPosition();

    void moveElmo(const bool isFoodEaten = false);

    bool isElmoEatingItself() const;

    static bool comparePoints(const SDL_Point& firstPoint, const SDL_Point& secondPoint);
private:
    std::list<SDL_Point> m_body;
    SDL_Point* m_head;
    SDL_Point* m_blockAfterHead;
    SDL_Point* m_tail;
    Direction m_direction;

    Direction getElmoDirection() const;
    void moveHead();
    void moveTail();
};

