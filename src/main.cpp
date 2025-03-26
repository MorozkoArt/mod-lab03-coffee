// Copyright 2022 UNN-IASR
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Automata.h"

int main() {
    Automata automata;
    automata.getState(std::cout);
    automata.on();
    std::vector<menu_item> menu = automata.getMenu();
    std::cout << "============ MENU ============\n";
    for (const auto& item : menu) {
        std::string name = item.name;
        double price = item.price;
        std::cout <<" Drink name: " << name << " Price: " << price << std::endl;
    }
    std::cout << "===============================\n";
    automata.getState(std::cout);
    automata.chois("Fanta", std::cout);
    automata.getState(std::cout);
    automata.coin(1.2, std::cout);
    return 0;
}
