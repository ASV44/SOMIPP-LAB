#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

class OrdersGenerator {

public:
  OrdersGenerator();
  OrdersGenerator(float maxDelay);

private:
  float maxDelay = 20;
  void startGeneratorThread();
  static void *generator(void * arg);
};
