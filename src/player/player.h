#pragma once
#include"../character/character.h"

class Player : public Character
{
private:
   void CollisionX() override;
   void CollisionY() override;
};