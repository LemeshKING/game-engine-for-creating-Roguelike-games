#pragma once


class Observer
{
 public:
   virtual ~Observer(){};
   virtual void HealthChange(const unsigned int& _currentHp) = 0;
   virtual void MoneyChange(const unsigned int& _currentMoney) = 0;
};