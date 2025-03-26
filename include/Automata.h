#ifndef AUTOMATA_H 
#define AUTOMATA_H

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

enum class STATES { OFF, WAIT, CHOIS, ACCEPT, CHECK, COOK };

struct menu_item {
    std::string name;  
    double price;
    menu_item(const std::string& n, double p) : name(n), price(p) {}   
};

class Automata {
public:

    class InvalidStateException : public std::runtime_error {
    public:
        InvalidStateException() : std::runtime_error("Invalid automata state") {}
    };
    
    class DrinkNotFoundException : public std::runtime_error {
    public:
        DrinkNotFoundException(const std::string& name) 
            : std::runtime_error("Drink not found: " + name) {}
    }; 

    class InvalidAmountException : public std::runtime_error {
    public:
        InvalidAmountException() : std::runtime_error("Amount must be positive") {}
    };

    Automata();
    STATES getState(std::ostream& os);
    std::vector<menu_item> getMenu();
    void on();
    void off();
    void chois(std::string name, std::ostream& os);
    void coin(double coin, std::ostream& os);
    void addMenu(std::string name, double price);
    void delMenu(std::string name);
    void cancel(std::ostream& os);

private:
    std::string role = "client";
    std::vector<menu_item> menu;
    STATES state = STATES::OFF;
    double cash = 0;
    menu_item* payment;
    void check(std::ostream& os);
    void cook(std::ostream& os);
    void finish(std::ostream& os);
    void change(double sum, std::ostream& os);
};
#endif 