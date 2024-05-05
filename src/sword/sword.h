#pragma once
#include "../Weapon/weapon.h"

class sword : public weapon
{
public:
   sword();
   void Attack() override;
};