#include "Restaurant.h"

vector<Order*> Restaurant::ordersList = vector<Order*> ();
pthread_mutex_t Restaurant::orderListLock;

Restaurant::Restaurant() {
  cout << "Restaurant created" << endl;
  cooksManager = new CooksManager();
  this->cooks = cooksManager->getCooks();
  this->cooks[0]->startCooking();
  this->cooks[2]->startCooking();
  this->work();
}

void  Restaurant::start() {
  pthread_mutex_init(&orderListLock, NULL);
  new Restaurant();
}

void Restaurant::work()
{
  while(true)
  {
    //cout << "Restaurant works" << endl;
    // if(ordersList.size() > 0)
    // {
    //   ordersList.back()->show();
    // }
    //sleep(5);
    checkFinisedOrder();
  }
}

void Restaurant::checkFinisedOrder()
{
  bool orderFinished;
  vector<int> toRemove = vector<int>();
  for(int i = 0; i < ordersList.size(); i++)
  {
    orderFinished = true;
    vector<Food*> foods = ordersList[i]->getItems();
    for(int j = 0; j < foods.size(); j++)
    {
      if(foods[j]->getStatus() != Food::DONE)
      {
        orderFinished = false;
        break;
      }
    }
    if(orderFinished) {
      toRemove.push_back(i);
      ordersList[i]->finishOrder();
    }
  }

  removeFinishedOrders(toRemove);
}

void Restaurant::removeFinishedOrders(vector<int> ordersListPosition)
{
  pthread_mutex_lock(&orderListLock);
  for(int i = 0; i < ordersListPosition.size(); i++)
  {
    ordersList.erase(ordersList.begin() + ordersListPosition[i]);
  }
  pthread_mutex_unlock(&orderListLock);
}
