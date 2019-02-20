#include "Lion.hpp"

using namespace std;

Lion::Lion() {
    hunger_level = 2200;
}

Animal::AnimalType Lion::type() const {
    // TODO: Implement
    return AT_LION;
}

unsigned int Lion::hungerLevel() const {
    // TODO: Implement 
    return hunger_level;
}

void Lion::resetToHungry() {
    // TODO: Implement
    hunger_level = 2200;
}

bool Lion::likesFood(const Food& food) const {
    // TODO: Implement
    if(food.getName() == "steak" || food.getName() == "mouse" || food.getName() == "fish")
    {
		return true;
    }
    else
    {
		return false;
    }
}

unsigned int Lion::feed(Food& food) {
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
