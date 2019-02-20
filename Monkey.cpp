#include "Monkey.hpp"

using namespace std;

Monkey::Monkey() {
    hunger_level = 800;
}

Animal::AnimalType Monkey::type() const {
    // TODO: Implement
    return AT_MONKEY;
}

unsigned int Monkey::hungerLevel() const {
    // TODO: Implement
    return hunger_level;
}

void Monkey::resetToHungry() {
    // TODO: Implement
    hunger_level = 800;
}

bool Monkey::likesFood(const Food& food) const {
    // TODO: Implement
    if(food.getName() == "banana"||food.getName() == "watermelon"||food.getName() == "mealworms")
    {
		return true;
    }
    else 
    {
		return false;
    }
}

unsigned int Monkey::feed(Food& food) {
    // TODO: Implement

    //arbitrary variable that stores the number of times the animal is fed
    unsigned int feedNumber = 0; 
   
    //while animal is still hungry and there's still food, keep feeding, and consume the food's quantity
    while(hunger_level > food.getEnergy() && food.getQuantity() > 0) 
    { 
      	hunger_level = hunger_level - food.getEnergy();
      	feedNumber++;
      	food.consume(1);
    }

    //if animial is still hungry(hunger_level!=0) and there's still food
    if(food.getEnergy() - hunger_level >= 0 && food.getQuantity() >= feedNumber + 1)
    {
		feedNumber++;
        hunger_level = 0;
        food.consume(1);
        return feedNumber;
    }
    //if animal is still hungry after being fed, but there is no food left	
    else if(food.getEnergy() - hunger_level > 0 && food.getQuantity() < feedNumber)
    {
        return feedNumber;
    }
    else 
	{
		return 0;
	}
}
