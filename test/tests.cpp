// Copyright 2026
#include "Automata.h"
#include <gtest/gtest.h>

TEST(AutomataTest, on_off) {
    Automata a;

    EXPECT_EQ(a.getState(), STATES::OFF);

    a.on();

    EXPECT_EQ(a.getState(), STATES::WAIT);

    a.off();

    EXPECT_EQ(a.getState(), STATES::OFF);
}

TEST(AutomataTest, insert_coin) {
    Automata a;

    a.on();

    a.coin(10.0);

    EXPECT_EQ(a.getCash(), 10.0);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);

    a.coin(20.0);

    EXPECT_EQ(a.getCash(), 30.0);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, successful_purchase) {
    Automata a;

    a.on();

    a.coin(10.0);
    a.coin(20.0);

    EXPECT_TRUE(a.choice(2));

    EXPECT_EQ(a.getState(), STATES::CHECK);

    EXPECT_TRUE(a.check());

    a.cook();

    EXPECT_EQ(a.getState(), STATES::COOK);

    a.finish();

    EXPECT_EQ(a.getCash(), 0.0);
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, insufficient_funds) {
    Automata a;

    a.on();

    a.coin(5.0);

    EXPECT_TRUE(a.choice(4));

    EXPECT_FALSE(a.check());

    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, cancel_operation) {
    Automata a;

    a.on();

    a.coin(15.0);

    EXPECT_EQ(a.getCash(), 15.0);

    a.cancel();

    EXPECT_EQ(a.getCash(), 0.0);
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, buy_tea) {
    Automata a;

    a.on();

    a.coin(20.0);

    EXPECT_TRUE(a.choice(1));

    EXPECT_TRUE(a.check());

    a.cook();

    EXPECT_EQ(a.getState(), STATES::COOK);

    a.finish();

    EXPECT_EQ(a.getState(), STATES::WAIT);
    EXPECT_EQ(a.getCash(), 0.0);
}

TEST(AutomataTest, invalid_choice) {
    Automata a;

    a.on();

    a.coin(50.0);

    EXPECT_FALSE(a.choice(10));

    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, cook_without_check) {
    Automata a;

    a.on();

    a.coin(30.0);

    a.cook();

    EXPECT_NE(a.getState(), STATES::COOK);
}

TEST(AutomataTest, finish_without_cook) {
    Automata a;

    a.on();

    a.coin(30.0);

    EXPECT_TRUE(a.choice(2));

    a.finish();

    EXPECT_EQ(a.getState(), STATES::CHECK);
}
TEST(AutomataTest, negative_coin) {
    Automata a;

    a.on();

    a.coin(-10.0);

    EXPECT_EQ(a.getCash(), 0.0);
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, zero_coin) {
    Automata a;

    a.on();

    a.coin(0.0);

    EXPECT_EQ(a.getCash(), 0.0);
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, choice_without_money) {
    Automata a;

    a.on();

    EXPECT_FALSE(a.choice(1));

    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, cancel_after_choice) {
    Automata a;

    a.on();

    a.coin(50.0);

    EXPECT_TRUE(a.choice(2));

    EXPECT_EQ(a.getState(), STATES::CHECK);

    a.cancel();

    EXPECT_EQ(a.getCash(), 0.0);
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, off_from_accept_state) {
    Automata a;

    a.on();

    a.coin(20.0);

    EXPECT_EQ(a.getState(), STATES::ACCEPT);

    a.off();

    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}
