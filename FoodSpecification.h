#include <string>

using namespace std;

struct FoodSpecification {
  float preparationTime;
  int complexity;
  string cookingApparatus;

  enum foodsType {PIZZA, SALAD, ZEAMA, SCALLOP,
                  DUCK, WAFFLES, AUBERGINE, LASAGNA};

  static string foodsName[];
};
