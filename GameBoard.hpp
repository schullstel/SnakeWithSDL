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

    const Elmo* getElmo() const;
    const Food* getFood() const;

    void setElmosDirection(const Elmo::Direction newDirection);
    Elmo::Direction getElmosDirection() const;

    bool isElmoOutOfBounds() const;
private:
    Elmo* m_elmo;
    Food* m_food;

    constexpr static uint16_t m_gameBoardWidht = 15;
    constexpr static uint16_t m_gameBoardHeight = 15;

    void generateElmoInTheMiddleOfBoard();
    void generateFoodInRandomPlace();

    bool isFoodEaten() const;
};

