#include "EnemyCreator.h"

UPtrEnemy WizardCreator::factoryMethod() const
{
   hlth::Health health;
   health.setHealthPoints(100);

   UPtrEnemy tmp = std::make_unique<Wizard>();


   tmp->setHealth(health);
   tmp->setCharacterHeight(50);
   tmp->setCharacterWidth(40);
   tmp->setDamageValue(10);

   return std::move(tmp);
}

UPtrEnemy ZombieCreator::factoryMethod() const
{
   hlth::Health health;
   health.setHealthPoints(100);

   UPtrEnemy tmp = std::make_unique<Enemy>();

   tmp->setHealth(health);
   tmp->setCharacterHeight(50);
   tmp->setCharacterWidth(40);
   tmp->setDamageValue(10);

   return std::move(tmp);
}

UPtrEnemy GhoulCreator::factoryMethod() const
{
   hlth::Health health;
   health.setHealthPoints(100);

   UPtrEnemy tmp = std::make_unique<Ghoul>();

   tmp->setHealth(health);
   tmp->setCharacterHeight(50);
   tmp->setCharacterWidth(40);
   tmp->setDamageValue(10);

   return std::move(tmp);
}
