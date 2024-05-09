#include "health.h"



hlth::Health::Health(unsigned int _maxHealthPoints)
{

   maxHealthPoints = _maxHealthPoints;
   healthPoints = _maxHealthPoints;
   if ((int)_maxHealthPoints <= 0)
   {
      maxHealthPoints = 100;
      healthPoints = 100;
   }
}

hlth::Health::Health()
{
   maxHealthPoints = 100;
   healthPoints = 100;
}

void hlth::Health::TakeDamage(int damageValue)
{
   if((int)healthPoints - damageValue > 0)
      healthPoints -= damageValue;
   else
      healthPoints = 0;

}
void hlth::Health::setMaxHealtPoints(unsigned int _MaxHealthPoints)
{
   maxHealthPoints = _MaxHealthPoints;
   if((int)_MaxHealthPoints <= 0)
      maxHealthPoints = 100;
}
void hlth::Health::setHealthPoints(unsigned int _healthPoints)
{
   
   healthPoints = _healthPoints;
   if((int)_healthPoints <= 0)
      healthPoints = 100;
}

unsigned int hlth::Health::getHealthPoints()
{
   return healthPoints;
}


unsigned int hlth::Health::getMaxHealthPoints()
{
   return maxHealthPoints;
}
