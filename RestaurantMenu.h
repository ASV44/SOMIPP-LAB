#include <string>
#include "json.hpp"
#include <fstream>
#include "RandomUtils.cpp"

#define MENU_FILE "RestaurantMenu.json"

using namespace std;

using json = nlohmann::json;

class RestaurantMenu {

public:
  static void init();
  static json menu;
  static std::vector<string> menuFoods;
  static int foodsAmount;
  static string getRandomFood();

private:


};
