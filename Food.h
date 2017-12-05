#include <string>
#include <iostream>
#include <vector>
#include "FoodSpecification.h"

using namespace std;

class Food {

public:
  Food(FoodSpecification::foodsType type);
  static const vector<FoodSpecification> typeOfFoods;
  void show();
  FoodSpecification::foodsType getType();
  float getPreparationTime();
  int getComplexity();
  string getCookingApparatus();

private:
  FoodSpecification::foodsType type;
  FoodSpecification specification;
};
