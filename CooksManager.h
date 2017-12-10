#include "Cook.h"
#include <vector>
#include "json.hpp"
#include <fstream>

using namespace std;
using json = nlohmann::json;

#define CooksList "Cooks.json"

class CooksManager {

public:
  CooksManager();
  vector<Cook*> getCooks();

private:
  vector<json> cooks;
};
