#include <vector>
#include "Food.h"
#include <chrono>

using namespace std;

class Order {

public:
  class Builder;
  void show();
  vector<Food*> getItems();
  int getPriority();
  float getMaxWait();
  bool hasFreeFoods(int rank);
  Food* getItem(int index);
  void finishOrder();
  int getOrderId();

private:
  Order(vector<Food*> items, int priority,
        float maxWait, int orderId);
  vector<Food*> items;
  int priority;
  float maxWait;
  int orderId;
  chrono::steady_clock::time_point orderStart;
};

class Order::Builder {

public:
  static const vector<Food*> defaultItems;
  static const int defaultPriority;
  static const float defaultMaxWait;
  static const int defaultOrderId;

  Builder() : items( defaultItems ), priority( defaultPriority ),
              maxWait( defaultMaxWait ), orderId( defaultOrderId ) { }

  Order::Builder& setItems( const vector<Food*> items);
  Order::Builder& setPriority( const int priority );
  Order::Builder& setMaxWait( const char maxWait );
  Order::Builder& setOrderId( const int orderId );

  Order* build();

private:
  vector<Food*> items;
  int priority;
  float maxWait;
  int orderId;
};
