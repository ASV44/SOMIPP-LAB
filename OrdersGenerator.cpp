#include "OrdersGenerator.h"

OrdersGenerator::OrdersGenerator() {
  startGeneratorThread();
}

OrdersGenerator::OrdersGenerator(int maxDelay) : maxDelay(maxDelay)
{
  startGeneratorThread();
}

void OrdersGenerator::startGeneratorThread()
{
  //generateOrder();
  pthread_t threadHandle;
  pthread_create(&threadHandle, NULL, generator, static_cast<void*>(&maxDelay));

  //pthread_join(threadHandle, NULL);
}

void* OrdersGenerator::generator(void* arg) {
  int delay = *(static_cast<int*>(arg));
  int generatedOrders = 0;
  while(true) {
    // pthread_mutex_lock(&Restaurant::orderListLock);
    cout << endl << "Generated Order #" << ++generatedOrders << endl;
    Restaurant::ordersList.push_back(generateOrder(generatedOrders));
    Restaurant::ordersList.back()->show();
    // pthread_mutex_unlock(&Restaurant::orderListLock);
    int random = RandomUtils::random(delay);
    sleep(random);
    // cout<< random << endl;
  }

  pthread_exit(NULL);
}

Order* OrdersGenerator::generateOrder(int orderId) {
  vector<Food*> foods;
  float maxWait = 0;
  int foodsAmount = RandomUtils::random(1, 5);
  for(int i = 0; i < foodsAmount; i++)
  {
    foods.push_back(new Food());
    if(maxWait < foods.back()->getPreparationTime())
    {
      maxWait = foods.back()->getPreparationTime();
    }
  }

  int priority  = RandomUtils::random(1, 5);

  maxWait *= 1.3;

  return Order::Builder().setItems(foods)
                         .setPriority(priority)
                         .setMaxWait(maxWait)
                         .setOrderId(orderId)
                         .build();
}
