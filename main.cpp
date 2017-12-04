#include <iostream>
#include "Restaurant.h"
#include "OrdersGenerator.h"

int main(int argc, char** argv) {

  new OrdersGenerator();
  Restaurant::start();
  return 0;
}
