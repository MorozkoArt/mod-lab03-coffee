// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include <sstream>
#include "Automata.h"

TEST(AutomataTest, StateOutput1) {
    Automata automata;
    std::stringstream output;
    automata.getState(output);
    EXPECT_EQ(output.str(), "OFF\n");
}

TEST(AutomataTest, StateOutput2) {
    Automata automata;
    std::stringstream output;
    automata.on();
    automata.getState(output);
    EXPECT_EQ(output.str(), "WAIT\n");
}

TEST(AutomataTest, StateOutput3) {
    Automata automata;
    std::stringstream output;
    automata.on();
    automata.chois("Fanta", output);
    output.str("");
    automata.getState(output);
    EXPECT_EQ(output.str(), "CHOIS\n");
}

TEST(AutomataTest, StateOutput4) {
    Automata automata;
    std::stringstream output;
    automata.on();
    automata.chois("Fanta", output);
    automata.coin(1.2, output);
    output.str("");
    automata.getState(output);
    EXPECT_EQ(output.str(), "WAIT\n");
}

TEST(AutomataTest, StateOutput5) {
    Automata automata;
    std::stringstream output;
    automata.on();
    automata.chois("Fanta", output);
    automata.coin(1.1, output);
    output.str("");
    automata.getState(output);
    EXPECT_EQ(output.str(), "CHOIS\n");
}

TEST(AutomataTest, MessageOutput1) {
    Automata automata;
    std::stringstream output;
    automata.on();
    automata.chois("Fanta", output);
    EXPECT_EQ(output.str(), "Selected: Fanta\n");
}

TEST(AutomataTest, MessageOutput2) {
    Automata automata;
    std::stringstream output;
    automata.on();
    automata.chois("Fanta", output);
    output.str("");
    automata.coin(1.2, output);
    EXPECT_EQ(output.str(),
        "Your drink(Fanta) has been successfully prepared!!!\n");
}

TEST(AutomataTest, MessageOutput3) {
    Automata automata;
    std::stringstream output;
    automata.on();
    automata.chois("Fanta", output);
    output.str("");
    automata.coin(1.3, output);
    EXPECT_EQ(output.str(),
        "Your change: 0.1$\n"
        "Your drink(Fanta) has been successfully prepared!!!\n");
}

TEST(AutomataExceptionTest, InvalidState) {
    Automata automata;
    std::stringstream output;
    EXPECT_THROW(automata.coin(1.0, output),
        Automata::InvalidStateException);
}

TEST(AutomataExceptionTest, InvalidState2) {
    Automata automata;
    std::stringstream output;
    EXPECT_THROW(automata.chois("Fanta", output),
        Automata::InvalidStateException);
}

TEST(AutomataExceptionTest, InvalidState3) {
    Automata automata;
    std::stringstream output;
    EXPECT_THROW(automata.off(),
        Automata::InvalidStateException);
}

TEST(AutomataExceptionTest, DrinkNotFound) {
    Automata automata;
    automata.on();
    std::stringstream output;
    EXPECT_THROW(automata.chois("UnknownDrink", output),
        Automata::DrinkNotFoundException);
}

TEST(AutomataExceptionTest, InvalidAmount) {
    Automata automata;
    automata.on();
    std::stringstream output;
    automata.chois("Fanta", output);
    EXPECT_THROW(automata.coin(-1.2, output),
        Automata::InvalidAmountException);
}

TEST(AutomataAdminTest, InAdmin) {
    Automata automata;
    automata.on();
    std::stringstream output;
    automata.chois("admin", output);
    output.str("");
    automata.getState(output);
    EXPECT_EQ(output.str(), "WAIT\n");
}

TEST(AutomataAdminTest, AddMenu) {
    Automata automata;
    automata.on();
    std::stringstream output;
    int startSize = automata.getMenu().size();
    automata.chois("admin", output);
    automata.addMenu("Pepsi", 1.9);
    int endSize = automata.getMenu().size();
    EXPECT_EQ(endSize, startSize+1);
}

TEST(AutomataAdminTest, DelMenu) {
    Automata automata;
    automata.on();
    std::stringstream output;
    int startSize = automata.getMenu().size();
    automata.chois("admin", output);
    automata.delMenu("Coffee");
    int endSize = automata.getMenu().size();
    EXPECT_EQ(endSize, startSize-1);
}
