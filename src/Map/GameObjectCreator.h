#include "../thorns/thorns.h"
#include "../teleport/teleport.h"

typedef std::shared_ptr<GameObject> SPtrGameObject;


class GameObjectCreator
{
public:
   virtual ~GameObjectCreator() {};
   virtual SPtrGameObject factoryMethod(IntVector &coords) const = 0;
};

class ThornsCreator : public GameObjectCreator
{
public:
   virtual ~ThornsCreator() {};
   SPtrGameObject factoryMethod(IntVector &coords) const override;
};

class TeleportCreator : public GameObjectCreator
{
public:
   virtual ~TeleportCreator() {};
   SPtrGameObject factoryMethod(IntVector &coords) const override;
};