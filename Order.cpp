#include "Order.h"

const vector<Food*> defaultItems = vector<Food*> ();
const int defaultPriority = 0;
const float defaultMaxWait = 0;

Builder& Order::Builder::setItems(const vector<Food*> items)
{
  this->items = items;
  return *this;
}

Builder& Order::Builder::setPriority(const int priority)
{
  this->priority = priority;
  return *this;
}

Builder& Order::Builder::setMaxWait(const char maxWait)
{
  this->maxWait = maxWait;
  return *this;
}

Order Order::Builder::build()
{
  return new Order(this->items, this-> priority, this->maxWait);
}
