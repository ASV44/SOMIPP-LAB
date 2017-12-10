#include "RestaurantMenu.h"

json RestaurantMenu::menu;
vector<string> RestaurantMenu::menuFoods = vector<string> ();
int RestaurantMenu::foodsAmount;

void RestaurantMenu::init() {
  ifstream inputFile;

  inputFile.open(MENU_FILE);
  if(inputFile.is_open()) {
      inputFile >> menu;
  }
  else {
      cout << "Read File was not open" << endl;
  }
  inputFile.close();

  foodsAmount = menu.size();

  for (auto element = menu.begin(); element != menu.end(); ++element)
  {
      menuFoods.push_back(element.key());
  }

  //cout << menu << endl;
}

string RestaurantMenu::getRandomFood()
{
  int random = RandomUtils::random(foodsAmount);
  return menuFoods[random];
}
