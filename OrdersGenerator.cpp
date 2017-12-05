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
  generateOrder();
  pthread_t threadHandle;
  pthread_create(&threadHandle, NULL, generator, static_cast<void*>(&maxDelay));

  //pthread_join(threadHandle, NULL);
}

void* OrdersGenerator::generator(void* arg) {
  int delay = *(static_cast<int*>(arg));
  while(true) {
    cout << "Running on the thread" << endl;
    int random = RandomUtils::random(delay);
    // cout<< random << endl;
    sleep(random);
  }

  pthread_exit(NULL);
}

Order* OrdersGenerator::generateOrder() {
  vector<Food*> foods;
  int foodsAmount = RandomUtils::random(1, 10);
  for(int i = 0; i < foodsAmount; i++)
  {
    FoodSpecification::foodsType type = static_cast<FoodSpecification::foodsType>(RandomUtils::random(Food::typeOfFoods.size()));
    foods.push_back(new Food(type));
    foods.back()->show();
  }

  return NULL;
}
