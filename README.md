## Eighte Minute Empire Game

### Introduction

In *Eight-Minute Empire*, 2-5 players take turns selecting a card from six displayed. The card gives a good, and also has an action that the player takes immediately. Actions help players take over the map, but sets of goods are worth points at the end of the game, so players have to balance the two aspects.

---

### Complilation

Assignment 1:
* There are 5 parimary parts of the project: Map, Maploadder, Card, bidding, and Player.
* Each part has its own header files, implementation files, and testing (dirver) files

Assignment 2:
* There are 6 Drivers for assignment 2; Each working with their own set of classes.

Part 1

* Driver: GameStartDriver.cpp
* Relevant files: GameStart.cpp, Maploader.cpp, Cards.cpp

Part 2
* Driver : StartupPhaseDriver.cpp
( Relevant files: StartupPhase.cpp, Cards.cpp, Player.cpp

Part 3 and Part 4
* Driver : PlayerActionsP4Driver.cpp
* Relevant files : MainGameLoopP3.cpp, Player.cpp, Cards.cpp, Map.cpp, Map.h

Part 5
* Driver : PlayerActionDriver.cpp
* Relevant files : Player.cpp, Cards.cpp, Map.cpp, Map.h

Part 6:
* Driver : ComputeScoreDriver.cpp
* Relevant files : Player.cpp, Cards.cpp, Map.cpp, Map.h

### Usage

* STL: string, vetor, map, array

---

### Assignment 3

#### Part 1: Player Strategy Pattern

* Description: three kinds of players: 
  * Human player that requires user interaction to make decisions
  * Greedy computer players that focus in building cities or destroying opponents
  * Moderate computer players that control a region in which it just needs to occupy it with more armies than the opponents
* Driver: PlayerStrategiesDriver.cpp
* Relevant files: PlayerStrategies.cpp, Player.cpp

#### Part 2: Phase Observer

* Description: Using observer design pattern, implement a view that displays information happening in the current turn
* Driver: ConcreteObserverDriver_A3P2.cpp
* Relevant files: Observer.h, Observer.cpp, StatisticsObserver.h,  StatisticsObserver.cpp, Player.h

#### Part 3: Game Statics Observer

* Description: Using observer design pattern, implement a view that displays some useful statistics about the game
* Driver: StatisticObserverDriver.cpp
* Relevant files: Observer.h, Observer.cpp, StatisticsObserver.h,  StatisticsObserver.cpp, Player.h

#### Part 4: Game Map Singleton

* Description: Using singleton design pattern, implement the structure and operation of a map for the game
* Driver: MapSingleton_A3P4Driver.cpp
* Relevant files: Map.h, Map.cpp. MapAss.cpp, MapLoader.cpp

---

### Assignment 4
#### Part 1 Cards Factory Pattern
* Using Factory Patthern to produce different types of cards. Card *card = CardsFactory::createCard(0)
* After drawing a cards from the CardSpace, using takeActions() to do the actions that the card provides



---




### Instrucitons

Instructions for the map and game components

#### Map

* The game is able to check and load any valid map file with extension *.map*

#### Continents

* Two continents can be connected by countries
* Each continents has several countries

#### Country

* Players can place armies in countries

#### Players

* 2-5 players, and each player's name, army color, and age should be determined at the beginning of the game. Besides, the initial tokens depend on the number of players

* ```c++
  Player("Liam", "Red", 20, 12)
  ```

#### Cards Deck

* There are 42 cards in one deck
* Each card represents different actions and goods

#### Bidding

* The ording of driving cards is determined by the bidding at the biginning of the game


