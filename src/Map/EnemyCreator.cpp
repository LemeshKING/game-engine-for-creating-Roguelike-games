#include "EnemyCreator.h"

SPtrEnemy WizardCreator::factoryMethod() const
{
   hlth::Health health;
   health.setHealthPoints(100);

   SPtrEnemy tmp = std::make_unique<Wizard>();


   tmp->setHealth(health);
   tmp->setCharacterHeight(50);
   tmp->setCharacterWidth(40);
   tmp->setDamageValue(10);

   return std::move(tmp);
}

SPtrEnemy ZombieCreator::factoryMethod() const
{
   hlth::Health health;
   health.setHealthPoints(100);

   SPtrEnemy tmp = std::make_unique<Enemy>();

   tmp->setHealth(health);
   tmp->setCharacterHeight(50);
   tmp->setCharacterWidth(40);
   tmp->setDamageValue(10);

   return std::move(tmp);
}

SPtrEnemy GhoulCreator::factoryMethod() const
{
   hlth::Health health;
   health.setHealthPoints(100);

   SPtrEnemy tmp = std::make_unique<Ghoul>();

   tmp->setHealth(health);
   tmp->setCharacterHeight(50);
   tmp->setCharacterWidth(40);
   tmp->setDamageValue(10);

   return std::move(tmp);
}
