#include "health.h"



hlth::Health::Health(unsigned int _maxHealthPoints)
{
   maxHealthPoints = _maxHealthPoints;
}

hlth::Health::Health()
{
   maxHealthPoints = 100;
}

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

unsigned int hlth::Health::getMaxHealthPoints()
{
   return maxHealthPoints;
}
