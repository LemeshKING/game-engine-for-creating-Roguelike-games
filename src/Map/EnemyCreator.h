#pragma once
#include"../Wizard/wizard.h"
#include"../Ghoul/Ghoul.h"

typedef std::shared_ptr<Enemy> SPtrEnemy;
typedef std::shared_ptr<Wizard> SPtrWizard;
typedef std::shared_ptr<Ghoul> SPtrGhoul;

class EnemyCreator
{
 public:

   virtual ~EnemyCreator() {};
   virtual SPtrEnemy factoryMethod() const = 0;
   
};

class WizardCreator : public EnemyCreator
{
 public:

   SPtrEnemy factoryMethod() const override;
};

class ZombieCreator : public EnemyCreator
{
public:

   SPtrEnemy factoryMethod() const override;
};

class GhoulCreator : public EnemyCreator
{
public:

   SPtrEnemy factoryMethod() const override;
};
