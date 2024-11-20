#pragma once
#include "../Observer/Observer.h"
#include<iostream>

typedef std::shared_ptr<Observer> SPtrObserver;

class ISubject
{
   
 public:
   virtual ~ISubject(){}
   virtual void Attach(SPtrObserver &observer) = 0;
   virtual void Detach(SPtrObserver &observer) = 0;
   virtual void Notify() = 0;



};