#pragma once
#include "../Map/map.h"

void gravity(PhysicalQuantities &pq, const float &time, const std::unique_ptr<mp::Map>& location);
void Collision(PhysicalQuantities &pq, const std::unique_ptr<mp::Map>& location);
void findingIntersections(Player &pl, const std::unique_ptr<mp::Map>& location);