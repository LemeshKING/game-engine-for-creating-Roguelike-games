#include "health.h"



void hlth::Health::TakeDamage(int damageValue)
{
   if((int)healthPoints - damageValue > 0)
      healthPoints -= damageValue;
   else
      healthPoints = 0;

}

void hlth::Health::setHealthPoints(unsigned int _healthPoints)
{
   healthPoints = _healthPoints;
}

unsigned int hlth::Health::getHealthPoints()
{
   return healthPoints;
}
