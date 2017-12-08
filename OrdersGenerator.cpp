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
  while(true) {
    cout << "Order generated" << endl;
    int random = RandomUtils::random(delay);
    generateOrder()->show();
    // cout<< random << endl;
    sleep(random);
  }

  pthread_exit(NULL);
}

Order* OrdersGenerator::generateOrder() {
  vector<Food*> foods;
  float maxWait = 0;
  int foodsAmount = RandomUtils::random(1, 10);
  for(int i = 0; i < foodsAmount; i++)
  {
    int randomFoodType = RandomUtils::random(Food::typeOfFoods.size());
    FoodSpecification::foodsType type = static_cast<FoodSpecification::foodsType>(randomFoodType);
    foods.push_back(new Food(type));
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
                         .build();
}
