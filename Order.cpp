#include "Order.h"

Order::Order(vector<Food*> items, int priority,
             float maxWait, int orderId) : items(items),
                                           priority(priority),
                                           maxWait(maxWait),
                                           orderId(orderId)
{
  this->orderStart = chrono::steady_clock::now();
}

void Order::show()
{
  for(int i = 0; i < this->items.size(); i++)
  {
    cout << this->items[i]->getName() << " ";
  }
  cout << endl << this->priority << endl;
  cout << this->maxWait << endl;
}

vector<Food*> Order::getItems()
{
  return this->items;
}

int Order::getPriority()
{
  return this->priority;
}

float Order::getMaxWait()
{
  return this->maxWait;
}

bool Order::hasFreeFoods(int rank)
{
  for(int i = 0; i < this->items.size(); i++)
  {
    if(this->items[i]->canTakeForPrepare(rank))
    {
      return true;
    }
  }

  return false;
}

Food* Order::getItem(int index)
{
  return this->items[index];
}

void Order::finishOrder()
{
  auto orderFinish = chrono::steady_clock::now();
  // cout << CLOCKS_PER_SEC << endl;
  // cout << this->orderStart << " ----- "<< orderFinish << endl;
  double elapsedTime = std::chrono::duration_cast<std::chrono::duration<double> >(orderFinish - this->orderStart).count();
  cout << endl;
  cout << "---------Order #" << this->orderId << " Has Been Finished in ";
  cout << elapsedTime <<"!---------" << endl;
  this->show();
  cout << endl;
}

int Order::getOrderId()
{
  return this->orderId;
}

const vector<Food*> Order::Builder::defaultItems = vector<Food*> ();
const int Order::Builder::defaultPriority = 0;
const float Order::Builder::defaultMaxWait = 0;
const int Order::Builder::defaultOrderId = -1;

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

Order::Builder& Order::Builder::setOrderId(const int orderId)
{
  this->orderId = orderId;
  return *this;
}

Order* Order::Builder::build()
{
  return new Order(this->items, this-> priority, this->maxWait, this->orderId);
}
