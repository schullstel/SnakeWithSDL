#include "RandomNumberGenerator.hpp"

#include <chrono>
#include <limits>

RandomNumberGenerator::RandomNumberGenerator()
{
    initializeIfNeeded();
    m_isInitialized = true;
}

RandomNumberGenerator& RandomNumberGenerator::getInstance()
{
    static RandomNumberGenerator randomNumberGenerator;
    return randomNumberGenerator;
}

int32_t RandomNumberGenerator::getRandomNumber(const int32_t& maxValue)
{
    return m_Distrib(m_Gen) % (maxValue + 1);
}

void RandomNumberGenerator::initializeIfNeeded()
{
    if (!m_isInitialized)
    {
        initializeRandomNumberGenerator();
    }
}

void RandomNumberGenerator::initializeRandomNumberGenerator()
{
    m_Seed = m_randomDevice() ^ (
                (std::mt19937::result_type)
                std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
                (std::mt19937::result_type)
                std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count());
    m_Gen = std::mt19937(m_Seed);
    m_Distrib = std::uniform_int_distribution<int32_t>(0, std::numeric_limits<int32_t>::max());
}
