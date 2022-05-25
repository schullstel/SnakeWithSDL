#pragma once

#include <stdint.h>

#include "Elmo.hpp"
#include "Food.hpp"

class GameBoard
{
public:
    GameBoard();
    ~GameBoard();

    void refreshBoard();

    void setElmosDirection(const Elmo::Direction newDirection);

    bool isElmoOutOfBounds() const;
    bool isElmoEatingItself() const;

    const Elmo* getElmo() const;
    const Food* getFood() const;
    Elmo::Direction getElmosDirection() const;
    uint32_t getScore() const;
    uint32_t getElmosLength() const;

    static uint16_t getGameBoardWidht();
    static uint16_t getGameBoardHeight();

private:
    Elmo* m_elmo;
    Food* m_food;
    uint32_t m_score;
    uint32_t m_elmosLength;

    constexpr static uint16_t m_gameBoardWidht = 15;
    constexpr static uint16_t m_gameBoardHeight = 15;

    void generateElmoInTheMiddleOfBoard();
    void generateFoodInRandomPlace();

    bool isFoodEaten() const;
};

