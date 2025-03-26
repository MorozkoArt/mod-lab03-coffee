#include "Automata.h"

Automata::Automata() {
    menu.push_back(menu_item("Fanta", 1.2));
    menu.push_back(menu_item("Cola", 1.3));
    menu.push_back(menu_item("Coffee", 1.4));
    menu.push_back(menu_item("Tea", 1.35));
    menu.push_back(menu_item("Water", 0.9));
}

std::vector<menu_item> Automata::getMenu(){
    return menu;
}

void Automata::on() {
    if (state == STATES::OFF) {
        state = STATES::WAIT;
    } else {
        throw InvalidStateException();
    }
}

void Automata::off(){
    if (state != STATES::OFF) {
        state = STATES::OFF;
        cash = 0;
    } else {
        throw InvalidStateException();
    }
}

void Automata::chois(std::string name, std::ostream& os){
    if (state == STATES::WAIT) {
        if (name == "admin") {
            role = "admin";
            os << "Role set to admin\n";
        } else if (name == "public") {
            role = "public";
            os << "Role set to public\n";
        } else {
            bool found = false;
            double value = 0;
            for (const auto& item : menu) {
                if (item.name == name) {
                    payment = new menu_item(name, item.price);
                    state = STATES::CHOIS;
                    os << "Selected: " << name << "\n";
                    return;
                }
            }
            throw DrinkNotFoundException(name);
        }
    } else {
        throw InvalidStateException();
    }
}

void Automata::coin(double coin, std::ostream& os) {
    if (coin <=0) {
        throw InvalidAmountException();
    } else if(state == STATES::CHOIS) {
        cash += coin;
        state = STATES::ACCEPT;
        check(os);
    } else if (state != STATES::CHOIS) {
        throw InvalidStateException();
    }
}

void Automata::check(std::ostream& os) {
    if (state == STATES::ACCEPT) {
        if (cash == payment->price) {
            state = STATES::CHECK;
            cook(os);
        }
        else if (cash > payment->price) {
            double surrender = cash - payment->price;
            change(surrender, os);
            state = STATES::CHECK;
            cook(os);      
        }
        else if (cash < payment->price) {
            state = STATES::CHOIS;
        }
    } else {
        throw InvalidStateException();
    }
}

void Automata::cancel(std::ostream& os) {
    if (state != STATES::OFF) {
        state = STATES::WAIT;
        delete payment;
        if (cash > 0) {
            change(cash, os);
        }       
    } else {
        throw InvalidStateException();
    }
}
void Automata::cook(std::ostream& os) {
    if (state == STATES::CHECK) {
        state = STATES::COOK;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        finish(os);
    } else {
        throw InvalidStateException();
    }
}

void Automata::finish(std::ostream& os) {
    if (state == STATES::COOK) {
        os << "Your drink("<< payment->name<<") has been successfully prepared!!!" <<std::endl;
        state = STATES::WAIT;
        cash = 0;
    } else {
        throw InvalidStateException();
    }
}

void Automata::change(double sum, std::ostream& os) {
    cash -= sum;
    os << "Your change: " << sum << "$" << std::endl;
}

void Automata::addMenu(std::string name, double price){
    if (role == "admin" && state == STATES::WAIT) {
        menu_item item(name, price);
        menu.push_back(item);
    }
}

void Automata::delMenu(std::string name) {
    if (role == "admin" && state == STATES::WAIT) {
        for (size_t i = 0; i < menu.size(); i++) {
            if (menu[i].name == name) {
                menu.erase(menu.begin() + i);
            }
        }
    }
}

STATES Automata::getState(std::ostream& os) {
    switch (state) {
        case STATES::OFF:
            os << "OFF" << std::endl;
            break;
        case STATES::WAIT:
            os << "WAIT" << std::endl;
            break;
        case STATES::CHOIS:
            os << "CHOIS" << std::endl;
            break;
        case STATES::ACCEPT:
            os << "ACCEPT" << std::endl;
            break;
        case STATES::CHECK:
            os << "CHECK" << std::endl;
            break;
        case STATES::COOK:
            os << "COOK" << std::endl;
            break;
    }
    return state;
}