#pragma once
#include<SFML/Graphics.hpp>

struct PhysicalQuantities
{
   float m = 0;
   sf::FloatRect rect;
   float dx = 0;
   float dy = 0;
   float elasticityCoefficient = 0.4;
};