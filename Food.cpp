#include "Food.hpp"
#include <string>

using namespace std;

Food::Food(const string& new_name, double new_cost, unsigned int new_energy) {
    name = new_name;
    cost = new_cost;
    energy = new_energy;
    current_quantity = 0;
}

string Food::getName() const {
    // TODO: Implement
    return name;
}

double Food::getCost() const {
    // TODO: Implement
    return cost;
}

unsigned int Food::getQuantity() const {
    // TODO: Implement
    return current_quantity;
}

unsigned int Food::getEnergy() const {
    // TODO: Implement
    return energy;
}

unsigned int Food::consume(unsigned int count) {
    // TODO: Implement
    current_quantity = current_quantity - count;
    return count;
}

void Food::purchase(unsigned int quantity) {
    // TODO: Implement
    current_quantity = current_quantity + quantity;
}
