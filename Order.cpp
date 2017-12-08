#include "Order.h"

void Order::show()
{
  for(int i = 0; i < this->items.size(); i++)
  {
    cout << this->items[i]->getName() << " ";
  }
  cout << endl << this->priority << endl;
  cout << this->maxWait << endl;
}

const vector<Food*> Order::Builder::defaultItems = vector<Food*> ();
const int Order::Builder::defaultPriority = 0;
const float Order::Builder::defaultMaxWait = 0;

Order::Builder& Order::Builder::setItems(const vector<Food*> items)
{
  this->items = items;
  return *this;
}

Order::Builder& Order::Builder::setPriority(const int priority)
{
  this->priority = priority;
  return *this;
}

Order::Builder& Order::Builder::setMaxWait(const char maxWait)
{
  this->maxWait = maxWait;
  return *this;
}

Order* Order::Builder::build()
{
  return new Order(this->items, this-> priority, this->maxWait);
}
