namespace hlth
{
   class Health
   {
      
    private:
      unsigned int healthPoints = 0;
      unsigned int maxHealthPoints;
    public:
      Health(unsigned int _maxHealthPoints);
      Health();
      void TakeDamage(int damageValue);
      void setHealthPoints(unsigned int _healthPoints);
      unsigned int getHealthPoints();
      unsigned int getMaxHealthPoints();
      
   };
}