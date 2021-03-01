# Roulette  

## Build
```
make simulation
```
## Run
```
./build/simulation.out

## Class description

### Player

It's able to calculate new bets according to the given list-based logic.
It follows the following conditions:
1. Needs to be added to a table before placing bets.
2. Needs to place a bet before getting bet results.
3. Needs to get bet results before placing a new bet.

### Roulette

Calculates a random (uniformly distributed) roulette number every time it is spun.
It's able to determine if a bet type is a winner or loser.

### Table

It contains a Roulette, an instance of TableRules and it's able to hold Players.
It manages the bet flow for each round (take bets, spin the roulette, distribute earnings).

### TableRules

It's able to determine if a bet is valid or not, according to its rules.

### BetDefs

General types and methods used throughout the program


