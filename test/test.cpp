#include "test.h"

#include "betdefs.h"

#include "player.h"
#include "roulette.h"
#include "tablerules.h"
#include "table.h"

#include <map>
#include <memory>
#include <vector>

#include <iostream>
#include <stdio.h>
#include <assert.h>

using namespace BetDefs;

void testPlayer();
void testRoulette();
void testTableRules();
void testTable();

void test()
{
    testPlayer();
    testRoulette();
    testTableRules();
    testTable();
}

void testPlayer()
{
    std::cout << "testPlayer" << std::endl;

    const std::vector<BetType> allBetTypes{BetType::Red, BetType::Black, BetType::Even, BetType::Odd, BetType::Low, BetType::High};

    std::map<BetType, std::shared_ptr<Player> > playerMap;

    for (auto betType : allBetTypes) {
        playerMap[betType] = std::make_shared<Player>(std::to_string(static_cast<unsigned int>(betType)), betType);
    }

    for (auto betType : allBetTypes) {
        // Test betType
        assert(betType == playerMap[betType]->getBetType());
    }

    auto playerA = std::make_shared<Player>("A", BetType::Red);

    // Test initial state
    assert(PlayerStatus::Idle == playerA->getStatus());
    assert(5 == playerA->getCurrentBet());
    assert(0 == playerA->getBalance());

    BetType betType;
    Money betAmount;

    // Player needs a table to sit on
    Table table;
    table.addPlayer(playerA);
    assert(PlayerStatus::WaitingToBet == playerA->getStatus());

    // Test state after loss
    playerA->takeBet(betType, betAmount);
    assert(PlayerStatus::WaitingForResult == playerA->getStatus());
    assert(5 == betAmount);
    playerA->onBetResult(BetResult::Lost, 0);
    assert(PlayerStatus::WaitingToBet == playerA->getStatus());
    assert(5 == playerA->getCurrentBet());
    assert(-5 == playerA->getBalance());
    
    // Test state after loss (should restart the list)
    playerA->takeBet(betType, betAmount);
    assert(PlayerStatus::WaitingForResult == playerA->getStatus());
    assert(5 == betAmount);
    playerA->onBetResult(BetResult::Lost, 0);
    assert(PlayerStatus::WaitingToBet == playerA->getStatus());
    assert(5 == playerA->getCurrentBet());
    assert(-10 == playerA->getBalance());

    // Test state after win
    playerA->takeBet(betType, betAmount);
    assert(PlayerStatus::WaitingForResult == playerA->getStatus());
    assert(5 == betAmount);
    playerA->onBetResult(BetResult::Won, 10);
    assert(PlayerStatus::WaitingToBet == playerA->getStatus());
    assert(6 == playerA->getCurrentBet());
    assert(-5 == playerA->getBalance());

    // Test state after win
    playerA->takeBet(betType, betAmount);
    assert(PlayerStatus::WaitingForResult == playerA->getStatus());
    assert(6 == betAmount);
    playerA->onBetResult(BetResult::Won, 12);
    assert(PlayerStatus::WaitingToBet == playerA->getStatus());
    assert(7 == playerA->getCurrentBet());
    assert(1 == playerA->getBalance());

    // Test state after loss
    playerA->takeBet(betType, betAmount);
    assert(PlayerStatus::WaitingForResult == playerA->getStatus());
    assert(7 == betAmount);
    playerA->onBetResult(BetResult::Lost, 0);
    assert(PlayerStatus::WaitingToBet == playerA->getStatus());
    assert(7 == playerA->getCurrentBet());
    assert(-6 == playerA->getBalance());

    // Test state after win
    playerA->takeBet(betType, betAmount);
    assert(PlayerStatus::WaitingForResult == playerA->getStatus());
    assert(7 == betAmount);
    playerA->onBetResult(BetResult::Won, 14);
    assert(PlayerStatus::WaitingToBet == playerA->getStatus());
    assert(9 == playerA->getCurrentBet());
    assert(1 == playerA->getBalance());

    // Test state if invalid
    playerA->takeBet(betType, betAmount);
    assert(PlayerStatus::WaitingForResult == playerA->getStatus());
    assert(9 == betAmount);
    playerA->onBetResult(BetResult::Invalid, betAmount);
    assert(PlayerStatus::WaitingToBet == playerA->getStatus());
    assert(5 == playerA->getCurrentBet());
    assert(1 == playerA->getBalance());
}

void testRoulette()
{
    std::cout << "testRoulette" << std::endl;

    Roulette roulette;

    // 0 makes any bet lose
    roulette._number = 0;
    assert(!roulette.isBetWinner(BetType::Red));
    assert(!roulette.isBetWinner(BetType::Black));
    assert(!roulette.isBetWinner(BetType::Even));
    assert(!roulette.isBetWinner(BetType::Odd));
    assert(!roulette.isBetWinner(BetType::Low));
    assert(!roulette.isBetWinner(BetType::High));

    // 10 is red, even, low
    roulette._number = 10;
    assert(!roulette.isBetWinner(BetType::Red));
    assert(roulette.isBetWinner(BetType::Black));
    assert(roulette.isBetWinner(BetType::Even));
    assert(!roulette.isBetWinner(BetType::Odd));
    assert(roulette.isBetWinner(BetType::Low));
    assert(!roulette.isBetWinner(BetType::High));
    
    // 21 is black, odd, high
    roulette._number = 21;
    assert(roulette.isBetWinner(BetType::Red));
    assert(!roulette.isBetWinner(BetType::Black));
    assert(!roulette.isBetWinner(BetType::Even));
    assert(roulette.isBetWinner(BetType::Odd));
    assert(!roulette.isBetWinner(BetType::Low));
    assert(roulette.isBetWinner(BetType::High));
}

void testTableRules()
{
    std::cout << "testTableRules" << std::endl;

    TableRules rules(1,10);

    // Check valid bets
    assert(rules.checkBet(1));
    assert(rules.checkBet(4));
    assert(rules.checkBet(5));
    assert(rules.checkBet(10));

    // Check invalid bets
    assert(!rules.checkBet(0));
    assert(!rules.checkBet(11));
    assert(!rules.checkBet(15));
    assert(!rules.checkBet(100));
}

void testTable()
{
    std::cout << "testTable" << std::endl;

    Table table;
    auto playerA = std::make_shared<Player>("A", BetType::Red);
    auto playerB = std::make_shared<Player>("B", BetType::Low);

    table.addPlayer(playerA);
    table.addPlayer(playerB);

    for (int i = 0; i < 100; i++) {
        // Total player balance must be the sum of the players' individual balance
        assert(table.getCurrentPlayersBalance() == (playerA->getBalance() + playerB->getBalance()));
        // Total player balance must be the opposite of the Table's balance
        assert(table.getCurrentPlayersBalance() == -table.getTableBalance());
        table.playRound();
    }
}