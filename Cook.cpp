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
         self->cookingData = findFoods(amount);
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

int Cook::findBestOrder()
{
  int priority = 0;
  int index  = -1;
  for(int i = 0; i < Restaurant::ordersList.size(); i++)
  {
    if(priority < Restaurant::ordersList[i]->getPriority() &&
       Restaurant::ordersList[i]->hasFreeFoods())
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
    currentOrder = findBestOrder();
    if (currentOrder == previousOrder || currentOrder == -1)
    {
      break;
    }
    vector<Food*> orderFoods = Restaurant::ordersList[currentOrder]->getItems();

    for(int i = 0; i < orderFoods.size() && specification.size() < amount; i++)
    {
      if(orderFoods[i]->canTakeForPrepare()) {
        specification.push_back({
          orderFoods[i],
          currentOrder
        });
        orderFoods[i]->setStatus(Food::PREPARING);
      }
    }
  }
  pthread_mutex_unlock(&Restaurant::orderListLock);
  //cout << "Amount " << amount << "Find foods" << specification.size() << endl;

  return specification;
}

void Cook::initSpeakingMutex()
{
  pthread_mutex_init(&speakingLock, NULL);
}
