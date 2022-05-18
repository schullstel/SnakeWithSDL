#pragma once

#include <stdint.h>
#include <SDL.h>

#include <list>

class Food
{
public:
    enum class FoodType
    {
        First = 0,
        Cheesecake = First,
        Banana,
        Sausage,
        Mochi,
        Last = Mochi,
        Unknown
    };

    Food();

    SDL_Point getFoodPosition() const;
    void setFoodPosition(const SDL_Point& newFoodPosition);

    FoodType getFoodType() const;
    void setFoodType(const FoodType newFoodType);

    FoodType getRandomFoodType();

    SDL_Point getRandomPostion(const std::list<SDL_Point>& snake,
                               const uint16_t& maxWidth,
                               const uint16_t& maxHeight);

private:
    SDL_Point m_foodPosition;
    FoodType m_foodType;

    bool isFoodInsideSnake(const std::list<SDL_Point>& snake,
                           const SDL_Point& food) const;
};

