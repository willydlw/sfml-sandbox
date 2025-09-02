#pragma once

#define __USE_MATH_DEFINES              // required on some platforms for M_PI
#include <cmath>

#include <SFML/System/Vector2.hpp>


template <typename T>
float calculateMagnitude(const sf::Vector2<T>& v)
{
    return std::sqrt(static_cast<float>(v.x * v.x + v.y * v.y));
}

template <typename T>
float calculateHeading(const sf::Vector2<T>& v)
{
    return std::atan2(v.y, v.x);
}

float radiansToDegrees(const float& angle)
{
    return angle * 180.f / M_PI;
}

float degreesToRadians(const float& angle)
{
    return angle * M_PI / 180.0f;
}