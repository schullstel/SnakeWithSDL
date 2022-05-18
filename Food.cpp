#include "Food.hpp"

#include "Tools/RandomNumberGenerator.hpp"

#include <iostream>

Food::Food()
{

}

SDL_Point Food::getFoodPosition() const
{
    return m_foodPosition;
}

void Food::setFoodPosition(const SDL_Point& newFoodPosition)
{
    m_foodPosition = newFoodPosition;
}

Food::FoodType Food::getFoodType() const
{
    return m_foodType;
}

void Food::setFoodType(const FoodType newFoodType)
{
    m_foodType = newFoodType;
}

Food::FoodType Food::getRandomFoodType()
{
    return static_cast<FoodType>(RandomNumberGenerator::getInstance().getRandomNumber(static_cast<uint32_t>(FoodType::Last)));
}

SDL_Point Food::getRandomPostion(const std::list<SDL_Point>& snake, const uint16_t& maxWidth, const uint16_t& maxHeight)
{
    SDL_Point newFeedPosition;
    do {
        int newX = RandomNumberGenerator::getInstance().getRandomNumber(maxWidth);
        int newY = RandomNumberGenerator::getInstance().getRandomNumber(maxHeight);
        newFeedPosition = SDL_Point( {newX, newY} );
    } while(isFoodInsideSnake(snake, newFeedPosition));

    return newFeedPosition;
}

bool Food::isFoodInsideSnake(const std::list<SDL_Point>& snake, const SDL_Point& food) const
{
    for (const SDL_Point& point : snake)
    {
        if (food.x == point.x && food.y == point.y)
        {
            return true;
        }
    }
    return false;
}
