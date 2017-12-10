#include "Restaurant.h"

vector<Order*> Restaurant::ordersList = vector<Order*> ();

Restaurant::Restaurant() {
  cout << "Restaurant created" << endl;
  cooksManager = new CooksManager();
  this->cooks = cooksManager->getCooks();
  this->cooks.back()->showSpecification();
  this->work();
}

void  Restaurant::start() {
  new Restaurant();
}

void Restaurant::work()
{
  while(true)
  {
    cout << "Restaurant works" << endl;
    if(ordersList.size() > 0)
    {
      ordersList.back()->show();
    }
    sleep(5);
  }
}
