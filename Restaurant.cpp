#include "Restaurant.h"
#include "Food.h"

Restaurant::Restaurant() {
  cout << "Restaurant created" << endl;

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
    sleep(5);
  }
}
