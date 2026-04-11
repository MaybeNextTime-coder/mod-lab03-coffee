// Copyright 2026

#include "Automata.h"

#include <iomanip>
#include <sstream>
#include <string>

Automata::Automata()
    : cash_(0.0),
      menu_({"Tea", "Coffee", "Milk", "Hot chocolate"}),
      prices_({15.0, 25.0, 20.0, 30.0}),
      state_(STATES::OFF),
      selected_item_(-1) {
}

void Automata::on() {
    if (state_ == STATES::OFF) {
        state_ = STATES::WAIT;
    }
}

void Automata::off() {
    if (state_ == STATES::WAIT) {
        state_ = STATES::OFF;
    }
}

void Automata::coin(double amount) {
    if ((state_ == STATES::WAIT || state_ == STATES::ACCEPT) &&
        amount > 0.0) {
        cash_ += amount;
        state_ = STATES::ACCEPT;
    }
}

std::string Automata::etMenu() const {
    std::ostringstream out;
    out << "Menu:\n";
    for (size_t i = 0; i < menu_.size(); ++i) {
        out << i + 1 << ". " << menu_[i] << " - "
            << std::fixed << std::setprecision(2) << prices_[i] << '\n';
    }
    return out.str();
}

STATES Automata::getState() const {
    return state_;
}

double Automata::getCash() const {
    return cash_;
}

bool Automata::choice(int item) {
    if (state_ != STATES::ACCEPT) {
        return false;
    }

    if (item < 1 || item > static_cast<int>(menu_.size())) {
        return false;
    }

    selected_item_ = item - 1;
    state_ = STATES::CHECK;
    return true;
}

bool Automata::check() {
    if (state_ != STATES::CHECK || selected_item_ == -1) {
        return false;
    }

    if (cash_ >= prices_[selected_item_]) {
        return true;
    }

    selected_item_ = -1;
    state_ = STATES::ACCEPT;
    return false;
}

void Automata::cancel() {
    if (state_ == STATES::WAIT ||
        state_ == STATES::ACCEPT ||
        state_ == STATES::CHECK) {
        cash_ = 0.0;
        selected_item_ = -1;
        state_ = STATES::WAIT;
    }
}

void Automata::cook() {
    if (state_ == STATES::CHECK &&
        selected_item_ != -1 &&
        cash_ >= prices_[selected_item_]) {
        state_ = STATES::COOK;
    }
}

void Automata::finish() {
    if (state_ != STATES::COOK || selected_item_ == -1) {
        return;
    }

    cash_ -= prices_[selected_item_];

    if (cash_ < 0.0) {
        cash_ = 0.0;
    }

    cash_ = 0.0;
    selected_item_ = -1;
    state_ = STATES::WAIT;
}
