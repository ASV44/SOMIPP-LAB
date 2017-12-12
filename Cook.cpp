#include "Cook.h"
#include "Restaurant.h"

pthread_mutex_t Cook::speakingLock;

void Cook::showSpecification()
{
  cout << this->name << endl;
  cout << this->rank << endl;
  cout << this->proficiency << endl;
  cout << this->catchPhrase << endl;
}

void Cook::startCooking()
{
  pthread_t threadHandle;
  pthread_mutex_init(&cookingLock, NULL);
  pthread_create(&threadHandle, NULL, orderSearching, this);
}

void* Cook::orderSearching(void *arg) {
  Cook *self = static_cast<Cook*>(arg);
  //cout << "Cook Thread" << endl;
  while(true) {
    if(self->currentCooking < self->proficiency &&
       self->cookingData.size() == 0)
       {
         int amount = self->proficiency - self->currentCooking;
         self->cookingData = self->findFoods(amount);
         int cookingDataAmount = self->cookingData.size();
         for(int i = 0; i < cookingDataAmount; i++)
         {
           pthread_t threadHandle;
           //void *arg = static_cast<void*>(&specification[i]);
           pthread_create(&threadHandle, NULL, cooking, self);
           //thread_join(threadHandle, NULL);
           self->currentCooking++;
         }
       }
     }
  //pthread_exit(NULL);
}

void* Cook::cooking(void *arg)
{
  Cook *self = static_cast<Cook*>(arg);

  pthread_mutex_lock(&self->cookingLock);
  Cook::CookingSpecification cookingData = self->cookingData.back();
  self->cookingData.pop_back();
  pthread_mutex_unlock(&self->cookingLock);

  self->startFoodCooking(cookingData);

  sleep(cookingData.food->getPreparationTime());

  self->finishFoodCooking(cookingData);

  pthread_exit(NULL);
}

void Cook::finishFoodCooking(Cook::CookingSpecification cookingData)
{
  Order *currentOrder = Restaurant::ordersList[cookingData.orderId];

  pthread_mutex_lock(&this->speakingLock);
  cout << this->name << ": Finished " << cookingData.food->getName();
  cout << " From Order #" << currentOrder->getOrderId() << "! ";
  cout << this->catchPhrase << endl;
  cookingData.food->setStatus(Food::DONE);
  pthread_mutex_unlock(&this->speakingLock);
  this->currentCooking--;
}

void Cook::startFoodCooking(Cook::CookingSpecification cookingData)
{
  Order *currentOrder = Restaurant::ordersList[cookingData.orderId];

  pthread_mutex_lock(&this->speakingLock);
  cout << this->name << " rank " << this->rank;
  cout << " : Starting to cook " << cookingData.food->getName();
  cout << " with complexity " << cookingData.food->getComplexity();
  cout << " From Order #" << currentOrder->getOrderId() << "! " << endl;
  pthread_mutex_unlock(&this->speakingLock);
}

int Cook::findBestOrder(int rank)
{
  int priority = 0;
  int index  = -1;
  for(int i = 0; i < Restaurant::ordersList.size(); i++)
  {
    if(priority < Restaurant::ordersList[i]->getPriority() &&
       Restaurant::ordersList[i]->hasFreeFoods(rank))
    {
      priority = Restaurant::ordersList[i]->getPriority();
      index = i;
    }
  }

  return index;
}

vector<Cook::CookingSpecification> Cook::findFoods(int amount)
{
  vector<Cook::CookingSpecification> specification = vector<Cook::CookingSpecification>();
  int currentOrder;
  int previousOrder = -1;

  pthread_mutex_lock(&Restaurant::orderListLock);
  while(specification.size() < amount) {
    currentOrder = findBestOrder(this->rank);
    if (currentOrder == previousOrder || currentOrder == -1)
    {
      break;
    }
    vector<Food*> orderFoods = Restaurant::ordersList[currentOrder]->getItems();

    for(int i = 0; i < orderFoods.size() && specification.size() < amount; i++)
    {
      if(orderFoods[i]->canTakeForPrepare(rank)) {
        specification.push_back({
          orderFoods[i],
          currentOrder
        });
        orderFoods[i]->setStatus(Food::PREPARING);
      }
    }

    previousOrder = currentOrder;
  }
  pthread_mutex_unlock(&Restaurant::orderListLock);
  //cout << "Amount " << amount << "Find foods" << specification.size() << endl;

  return specification;
}

void Cook::initSpeakingMutex()
{
  pthread_mutex_init(&speakingLock, NULL);
}
