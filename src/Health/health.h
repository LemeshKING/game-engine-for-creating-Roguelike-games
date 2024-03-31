namespace hlth
{
   class Health
   {
      
    private:
      unsigned int healthPoints = 0;
    public:
      void TakeDamage(int damageValue);
      void setHealthPoints(unsigned int _healthPoints);
      unsigned int getHealthPoints();
      
   };
}