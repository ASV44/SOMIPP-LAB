#ifndef Restaurant_H
#define Restaurant_H
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include "Order.h"
#include "CooksManager.h"

#define TIME_UNIT 1
#define TABLES 10

using namespace std;

class Restaurant {

public:
  Restaurant();
  static void start();
  void work();
  static vector<Order*> ordersList;
  void checkFinisedOrder();
  static pthread_mutex_t orderListLock;
  static void removeFinishedOrders(vector<int> ordersListPosition);

private:
  CooksManager *cooksManager;
  vector<Cook*> cooks;
};

#endif
