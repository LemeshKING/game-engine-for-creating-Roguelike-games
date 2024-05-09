namespace hlth
{
   class Health
   {
      
    private:
      unsigned int healthPoints = 0;
      unsigned int maxHealthPoints = 0;
    public:
      Health(unsigned int _maxHealthPoints);
      Health();
      void TakeDamage(int damageValue);
      void setHealthPoints(unsigned int _healthPoints);
      void setMaxHealtPoints(unsigned int _MaxHealthPoints);
      unsigned int getHealthPoints();
      unsigned int getMaxHealthPoints();
      
   };
}