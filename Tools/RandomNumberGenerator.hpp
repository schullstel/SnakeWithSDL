#pragma once

#include <random>

class RandomNumberGenerator
{
public:
    RandomNumberGenerator(RandomNumberGenerator const&) = delete;
    void operator=(RandomNumberGenerator const&) = delete;

    static RandomNumberGenerator& getInstance();

    int32_t getRandomNumber(const int32_t& maxValue);
private:
    RandomNumberGenerator();

    void initializeIfNeeded();
    void initializeRandomNumberGenerator();
private:
    bool m_isInitialized;

    std::random_device m_randomDevice;
    std::mt19937::result_type m_Seed;
    std::mt19937 m_Gen;
    std::uniform_int_distribution<int32_t> m_Distrib;
};

