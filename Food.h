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

private:
  string name;
  float preparationTime;
  int complexity;
  string cookingApparatus;
};
