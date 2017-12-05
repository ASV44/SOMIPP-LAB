#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "RandomUtils.cpp"
#include "Order.h"
#include <vector>

using namespace std;

class OrdersGenerator {

public:
  OrdersGenerator();
  OrdersGenerator(int maxDelay);
  Order* generateOrder();

private:
  int maxDelay = 20;
  void startGeneratorThread();
  static void *generator(void * arg);
};
