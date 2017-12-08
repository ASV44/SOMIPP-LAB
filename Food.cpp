#include "Food.h"

Food::Food(FoodSpecification::foodsType type)
{
  this->type = type;
  this->specification.preparationTime = typeOfFoods[type].preparationTime;
  this->specification.complexity = typeOfFoods[type].complexity;
  this->specification.cookingApparatus = typeOfFoods[type].cookingApparatus;
}

void Food::show() {
  cout << endl << this->getName() << endl;
  cout << "preparation time: " << this->specification.preparationTime << endl;
  cout << "complexity: " << this->specification.complexity << endl;
  cout << "cooking Apparatus: " << this->specification.cookingApparatus << endl;
}

FoodSpecification::foodsType Food::getType()
{
  return this->type;
}

float Food::getPreparationTime()
{
  return this->specification.preparationTime;
}

int Food::getComplexity()
{
  return this->specification.complexity;
}

string Food::getCookingApparatus()
{
  return this->specification.cookingApparatus;
}

string Food::getName()
{
  int type = this->type;
  return FoodSpecification::foodsName[type];
}

const vector<FoodSpecification> Food::typeOfFoods = {
  {
    20, //preparation_Time
    2, //complexity
    "oven" //cooking Apparatus
  },
  {
    10, //preparation_Time
    1, //complexity+
    "" //cooking Apparatus
  },
  {
    7, //preparation_Time
    1, //complexity
    "stove" //cooking Apparatus
  },
  {
    32, //preparation_Time
    3, //complexity
    "" //cooking Apparatus
  },
  {
    35, //preparation_Time
    3, //complexity
    "oven" //cooking Apparatus
  },
  {
    10, //preparation_Time
    1, //complexity
    "stove" //cooking Apparatus
  },
  {
    20, //preparation_Time
    2, //complexity
    "" //cooking Apparatus
  },
  {
    30, //preparation_Time
    2, //complexity
    "oven" //cooking Apparatus
  },
};
