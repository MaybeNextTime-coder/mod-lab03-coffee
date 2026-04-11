// Copyright 2026

#include <iostream>

#include "Automata.h"

int main() {
    Automata machine;

    std::cout << "=== Scenario 1: successful purchase ===\n";
    machine.on();
    std::cout << machine.etMenu();
    machine.coin(10.0);
    machine.coin(20.0);

    if (machine.choice(2)) {
        if (machine.check()) {
            machine.cook();
            machine.finish();
            std::cout << "Coffee prepared successfully\n";
        } else {
            std::cout << "Not enough money for selected drink\n";
        }
    }

    std::cout << "\n=== Scenario 2: cancel operation ===\n";
    machine.coin(15.0);
    machine.cancel();
    std::cout << "Operation cancelled\n";

    std::cout << "\n=== Scenario 3: insufficient funds ===\n";
    machine.coin(5.0);
    if (machine.choice(4)) {
        if (!machine.check()) {
            std::cout << "Not enough money for hot chocolate\n";
        }
    }
    machine.cancel();

    std::cout << "\n=== Scenario 4: buy tea ===\n";
    machine.coin(20.0);
    if (machine.choice(1) && machine.check()) {
        machine.cook();
        machine.finish();
        std::cout << "Tea prepared successfully\n";
    }

    machine.off();
    std::cout << "\nMachine switched off\n";

    return 0;
}

