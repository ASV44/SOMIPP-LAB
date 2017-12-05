#include <vector>
#include "Food.h"

using namespace std;

class Order {

public:
  class Builder;

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

  Builder& setItems( const vector<Food*> items);
  Builder& setPriority( const int priority );
  Builder& setMaxWait( const char maxWait );

  Order build();

private:
  vector<Food*> items;
  int priority;
  float maxWait;
};
