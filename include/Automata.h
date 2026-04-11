// Copyright 2026 Danya

#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include <string>
#include <vector>

enum class STATES {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK
};

class Automata {
 public:
    Automata();

    void on();
    void off();
    void coin(double amount);
    std::string etMenu() const;
    STATES getState() const;
    double getCash() const;
    bool choice(int item);
    bool check();
    void cancel();
    void cook();
    void finish();

 private:
    double cash_;
    std::vector<std::string> menu_;
    std::vector<double> prices_;
    STATES state_;
    int selected_item_;
};

#endif  // INCLUDE_AUTOMATA_H_
