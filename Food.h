#ifndef Food_H
#define Food_H
#include <string>
#include <iostream>
#include <vector>
#include "RestaurantMenu.h"

using namespace std;

class Food {

public:
  Food();
  Food(string foodName);
  void show();
  float getPreparationTime();
  int getComplexity();
  string getCookingApparatus();
  string getName();
  void initSpecification(string foodName);
  enum Status { NOT_TAKEN, PREPARING, DONE};
  bool canTakeForPrepare();
  void setStatus(Status status);
  Status getStatus();

private:
  string name;
  float preparationTime;
  int complexity;
  string cookingApparatus;
  Status status;
};

#endif
