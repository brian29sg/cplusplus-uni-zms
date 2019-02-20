#include "ZooManagementSystem.hpp"

using namespace std;

ZooManagementSystem::ZooManagementSystem(double initialBalance) {
	balance = initialBalance;
}

ZooManagementSystem::~ZooManagementSystem() {
    // TODO: Implement

    //scan through the vector containing pointers to Animal, and delete those at the heap. Clears the contents as well.
    for(unsigned int i= 0; i < pointer.size(); i++)
    {
 		delete pointer[i];
    }
    pointer.clear();
}

string ZooManagementSystem::author() {
    // TODO: Implement
    return "bbal548";
}

double ZooManagementSystem::getBalance() const {
    // TODO: Implement
    return balance;
}

double ZooManagementSystem::admitVisitors(unsigned int adults, unsigned int children) {
    // TODO: Implement

    //assumes that transactions occur per family
    //arbitrary variable that holds the total amount due by a family
    unsigned int cost_total;
    
    //assumes one family pass
    if(children > adults)
    {
		cost_total = 14 * adults + 5 * children - 8;
    }

    //assumes the 2 or more "family pass"
    else if(children == adults && adults % 2 == 0)
    {
		cost_total = (adults / 2) * 30;
    }
    else
    {
        cost_total = 14 * adults + 5 * children;
    }
    balance = balance + cost_total;//adds the total profit to the Zoo's balance
    return cost_total;
}

vector<Food> ZooManagementSystem::getFood() const {
    // TODO: Implement
    return food_type;
}

void ZooManagementSystem::addFood(const Food& new_food) {
    // TODO: Implement
    food_type.push_back(new_food);
}

bool ZooManagementSystem::purchaseFood(double& cost, unsigned int index, unsigned int quantity) {
    // TODO: Implement

    //respective calculations done here
    double foodCost = food_type[index].getCost();
    double totalCost = foodCost * quantity;
    double netBalance = balance - totalCost;

    //as long as the balance is not "negative"
    if(netBalance >= 0)
    {
		cost = totalCost;
        balance = netBalance;
        food_type[index].purchase(quantity);
        return true;
    }                                                                                                                                                                                                     
    
    //if index exceeds the size of the food_type vector
    else if(index >= food_type.size())
    {
		cost = 0.0;
        return false;
    }

    //cancels purchase if the balance reaches below zero. Still returns the total cost
    else if(netBalance < 0)
    {
		cost = totalCost;
		return false;
    }
    else
    {
		return false;
    }
}
                                                                                                                                
vector<Animal*> ZooManagementSystem::getAnimals() const {
    // TODO: Implement
    return pointer;
}

bool ZooManagementSystem::addAnimal(Animal::AnimalType new_animal_type) {
    // TODO: Implement
    switch(new_animal_type)
    {
		case Animal::AT_MONKEY:
			pointer.push_back(new Monkey());
        	return true;
			break;
        case Animal::AT_LION:
			pointer.push_back(new Lion());
			return true;
   			break;
		case Animal::AT_ELEPHANT:
        	pointer.push_back(new Elephant());
			return true;
   			break;
		case Animal::AT_SNAKE:
        	pointer.push_back(new Snake());
			return true;
   			break;
		case Animal::AT_OTTER:
        	pointer.push_back(new Otter());
			return true;
   			break;
		default:
			return false;
        	break;
	}
		
}

ZooManagementSystem::FeedResult ZooManagementSystem::feedAnimal(unsigned int& quantity_eaten, unsigned int animal_index, unsigned int food_index) {
    // TODO: Implement
    
    //checks whether animal_index is more than the vector size of "pointer"
    //or if the food_index exceeds the food_type vector's size
    if(animal_index >= pointer.size() || food_index >= food_type.size())
    {
		return FR_INVALID_ANIMAL;
    }

    //checks whether food_index has gone beyond the boundaries of the food_type vector
    else if(food_index >= food_type.size())
    {
		return FR_INVALID_FOOD;
    }

    //by default, these will be run respectively: checking of dislikes of the animal,
    //checking whether feeding was successful, and whether we have run out of food
    else
    {
		if(pointer[animal_index]->likesFood(food_type[food_index]) == false)
    	{
			return FR_INCOMPATIBLE;
		}
    	else
    	{ 
        	quantity_eaten = pointer[animal_index]->feed(food_type[food_index]);

            //checks the hunger level, and cross checks 
            //if we have run out of food but the animal's still hungry
	    	if(pointer[animal_index]->hungerLevel() == 0)
            {
				return FR_SUCCESS;
            }
	    	else
            {
				return FR_EXHAUSTED;
            }
    	}
     }
}

void ZooManagementSystem::resetAllAnimals() {
    // TODO: Implement

    //scans through the pointer vector, and accesses the reset 
    //of each animal 
    for(unsigned int a = 0; a < pointer.size(); a++)
    {
	pointer[a]->resetToHungry();
    }
}

void ZooManagementSystem::feedAllAnimals() {
    // TODO: Implement (leave until Task 4)
    
    vector<Animal*> hungriest;         //a vector that will consist of only one hungriest animal
    vector<unsigned int> position_fav; //a vector that stores the position value of an animal's favorite food in the food_type vector
    unsigned int counter = 0;   //arbitrary counter to access a specific pointer in the animal pointer vector

    /*finds the hungriest animal*/
    for(vector<Animal*>::iterator it = pointer.begin(); it != pointer.end(); ++it)
    {
		//first, fill up the "hungriest" vector
		if(hungriest.size() == 0)
		{
			hungriest.push_back(*it);
		}
		//next, check whether the current animal is hungrier than the one in "hungriest".
		//if it is, replace it.
		else if(pointer[counter]->hungerLevel() > hungriest[0]->hungerLevel())
		{
			hungriest.pop_back();
        	hungriest.push_back(*it);
		}

    	counter++;

    }

	counter = 0;

     /*searches the position in the "food_type" vector, which food the hungriest animal likes*/
     for(vector<Food>::iterator foo = food_type.begin(); foo != food_type.end(); ++foo)
     {
		if(hungriest[0]->likesFood(*foo))
		{
			//places the postion # of their favourite food into another vector called position_fav
			position_fav.push_back(counter);
		}
        counter++;
     }

     counter = 0;

     // finds the most abundant food among the favorites.
     // then deletes the ones with the least quantity.
     for(vector<unsigned int>::iterator fav = position_fav.begin(); fav != position_fav.end(); ++fav)
     {
		if(position_fav.size() > 1 && food_type[position_fav[*fav]].getQuantity() >= food_type[position_fav[counter+1]].getQuantity())
		{
			position_fav.erase(position_fav.begin()+1);
		}
		else if(position_fav.size() > 1 && food_type[position_fav[*fav]].getQuantity() < food_type[position_fav[counter+1]].getQuantity())
		{
			position_fav.erase(position_fav.begin());
		}
		else if(position_fav.size() == 1)
		{
			break; //exits out of the loop if the size becomes 1
		}
	 }

     hungriest[0]->feed(food_type[position_fav[0]]);//initiates the auto feeding
}
