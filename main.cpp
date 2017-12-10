#include <iostream>
// #include "Restaurant.h"
#include "OrdersGenerator.h"
#include <stdlib.h>

int main(int argc, char** argv) {

  srand(time(NULL));

  RestaurantMenu::init();
  new OrdersGenerator();
  Restaurant::start();
  return 0;
}
