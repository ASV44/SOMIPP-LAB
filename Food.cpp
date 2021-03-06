#include "Food.h"

Food::Food()
{
  initSpecification(RestaurantMenu::getRandomFood());
}

Food::Food(string foodName)
{
  initSpecification(foodName);
}

void Food:: initSpecification(string foodName)
{
  this->name = foodName;
  this->preparationTime = RestaurantMenu::menu[foodName]["preparation-time"];
  this->complexity = RestaurantMenu::menu[foodName]["complexity"];
  this->cookingApparatus = RestaurantMenu::menu[foodName]["cooking-apparatus"];
  this->status = NOT_TAKEN;
}

void Food::show() {
  cout << endl << this->name << endl;
  cout << "preparation time: " << this->preparationTime << endl;
  cout << "complexity: " << this->complexity << endl;
  cout << "cooking Apparatus: " << this->cookingApparatus << endl;
}

string Food::getName()
{
  return this->name;
}

float Food::getPreparationTime()
{
  return this->preparationTime;
}

int Food::getComplexity()
{
  return this->complexity;
}

string Food::getCookingApparatus()
{
  return this->cookingApparatus;
}

bool Food::canTakeForPrepare(int rank)
{
  return status == NOT_TAKEN && (rank == this->complexity || rank == this->complexity + 1);
}

void Food::setStatus(Status status)
{
  this->status = status;
}

Food::Status Food::getStatus()
{
  return this->status;
}
