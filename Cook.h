#include <string>
#include <iostream>

using namespace std;

class Cook {

public:
  Cook(string name, int rank,
       int proficiency, string catchPhrase) : name(name),
                                              rank(rank),
                                              proficiency(proficiency),
                                              catchPhrase(catchPhrase) {};

  void showSpecification();

private:
  string name;
  int rank;
  int proficiency;
  string catchPhrase;
};
