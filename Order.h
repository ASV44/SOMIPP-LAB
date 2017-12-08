#include <vector>
#include "Food.h"

using namespace std;

class Order {

public:
  class Builder;
  void show();

private:
  Order(vector<Food*> items, int priority, float maxWait) : items(items),
                                                           priority(priority),
                                                           maxWait(maxWait) {};
  vector<Food*> items;
  int priority;
  float maxWait;
};

class Order::Builder {

public:
  static const vector<Food*> defaultItems;
  static const int defaultPriority;
  static const float defaultMaxWait;

  Builder() : items( defaultItems ), priority( defaultPriority ), maxWait( defaultMaxWait ){ }

  Order::Builder& setItems( const vector<Food*> items);
  Order::Builder& setPriority( const int priority );
  Order::Builder& setMaxWait( const char maxWait );

  Order* build();

private:
  vector<Food*> items;
  int priority;
  float maxWait;
};
