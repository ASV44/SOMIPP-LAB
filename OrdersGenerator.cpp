#include "OrdersGenerator.h"

OrdersGenerator::OrdersGenerator() {
  startGeneratorThread();
}

OrdersGenerator::OrdersGenerator(float maxDelay) : maxDelay(maxDelay)
{
  startGeneratorThread();
}

void OrdersGenerator::startGeneratorThread()
{
  pthread_t threadHandle;

  pthread_create(&threadHandle, NULL, generator, NULL);

  //pthread_join(threadHandle, NULL);
}

void* OrdersGenerator::generator(void *arg) {
  while(true) {
    cout << "Running on the thread" << endl;
    sleep(2);
  }

  pthread_exit(NULL);
}
