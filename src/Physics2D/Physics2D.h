#pragma once
#include "../Map/map.h"

void gravity(SPtrWeapon &weapon, const float& time, const std::unique_ptr<mp::Map> &location);
void gravity(SPtrGameObject &gameObject, const float& time, const std::unique_ptr<mp::Map> &location);
void gravity(Character &character, const float &time ,const std::unique_ptr<mp::Map> &location);
void Collision(SPtrGameObject& gameObject, const std::unique_ptr<mp::Map>& location);
void Collision(SPtrWeapon& weapon, const std::unique_ptr<mp::Map>& location);
