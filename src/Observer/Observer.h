#pragma once


class Observer
{
 public:
   virtual ~Observer(){};
   virtual void HealthChange(const unsigned int& _currentHp) = 0;
};