#include <string>
#include <iostream>

using namespace std;

class Food {

private:
  struct FoodSpecification {
    float preparationTime;
    int complexity;
    string cookingApparatus;
  };

  FoodSpecification specification;

  static const FoodSpecification typeOfFoods[];

public:
  enum foodsType {PIZZA, SALAD, ZEAMA, SCALLOP,
                  DUCK, WAFFLES, AUBERGINE, LASAGNA};
  Food(foodsType type);

  void show();
};
