#include <iostream>
#include <pthread.h>
#include <unistd.h>

#define TIME_UNIT 1
#define TABLES 10

using namespace std;

class Restaurant {

public:
  Restaurant();
  static void start();
  void work();

private:
  
};
