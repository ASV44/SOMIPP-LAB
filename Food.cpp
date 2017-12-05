#include "Food.h"

Food::Food(FoodSpecification::foodsType type)
{
  this->type = type;
  this->specification.preparationTime = typeOfFoods[type].preparationTime;
  this->specification.complexity = typeOfFoods[type].complexity;
  this->specification.cookingApparatus = typeOfFoods[type].cookingApparatus;
}

void Food::show() {
  std::cout << this->specification.preparationTime << '\n';
  std::cout << this->specification.complexity << '\n';
  std::cout << this->specification.cookingApparatus << '\n';
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
