#ifndef Cook_H
#define Cook_H
#include <string>
#include <iostream>
#include "Food.h"

using namespace std;

class Cook {

public:
  Cook(string name, int rank,
       int proficiency, string catchPhrase) : name(name),
                                              rank(rank),
                                              proficiency(proficiency),
                                              catchPhrase(catchPhrase) {};

  struct CookingSpecification {
    Food* food;
    int orderId;
  };

  void showSpecification();
  void startCooking();
  static void *orderSearching(void *arg);
  bool isCooking = false;
  int currentCooking = 0;
  pthread_mutex_t cookingLock;
  static void *cooking(void *arg);
  vector<Cook::CookingSpecification> cookingData;
  static pthread_mutex_t speakingLock;
  static void initSpeakingMutex();
  void finishFoodCooking(Cook::CookingSpecification cookingData);

private:
  string name;
  int rank;
  int proficiency;
  string catchPhrase;
  static vector<Cook::CookingSpecification> findFoods(int amount);
  static int findBestOrder();
};

#endif
