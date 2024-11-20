#pragma once
#include"../Wizard/wizard.h"
#include"../Ghoul/Ghoul.h"

typedef std::unique_ptr<Enemy> UPtrEnemy;
typedef std::unique_ptr<Wizard> UPtrWizard;
typedef std::unique_ptr<Ghoul> UPtrGhoul;

class EnemyCreator
{
 public:

   virtual ~EnemyCreator() {};
   virtual UPtrEnemy factoryMethod() const = 0;
   
};

class WizardCreator : public EnemyCreator
{
 public:

   UPtrEnemy factoryMethod() const override;
};

class ZombieCreator : public EnemyCreator
{
public:

   UPtrEnemy factoryMethod() const override;
};

class GhoulCreator : public EnemyCreator
{
public:

   UPtrEnemy factoryMethod() const override;
};
