#include "CooksManager.h"

CooksManager::CooksManager()
{
  ifstream inputFile;
  json cooks;

  this->cooks = vector<json> ();

  inputFile.open(CooksList);
  if(inputFile.is_open()) {
      inputFile >> cooks;
  }
  else {
      cout << "Read File was not open" << endl;
  }
  inputFile.close();

  for(int i = 0; i < cooks["cooks"].size(); i++) {
    this->cooks.push_back(cooks["cooks"][i]);
  }
}

vector<Cook*> CooksManager::getCooks()
{
  Cook::initSpeakingMutex();
  std::vector<Cook*> availableCooks = std::vector<Cook*> ();
  int cooksAmount = cooks.size();
  for(int i = 0; i < cooksAmount; i++) {
    availableCooks.push_back(new Cook(cooks[i]["name"],
                                      cooks[i]["rank"],
                                      cooks[i]["proficiency"],
                                      cooks[i]["catch-phrase"]));
  }

  return availableCooks;
}
