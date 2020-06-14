#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "Classes.h"

void fillDeck(std::vector<Card> &deck)
{
  while (deck.size() > 1)
  {
    deck.pop_back();
  }
  for (int i = 1; i <= 4; i++)
  {
    for (int j = 1; j <= 13; j++)
    {
      Suit suit(i);
      Card card(suit, j);
      deck.push_back(card);
    }
  }
}

void displayDeck(std::vector<Card> deck)
{
  std::cout << std::endl
            << "contents of deck: " << std::endl;
  for (int i = 0; i < deck.size(); i++)
  {
    std::cout << deck.at(i).getName() << " of " << deck.at(i).getSuit().getSuitName() << std::endl;
  }
}

void shuffleDeck(std::vector<Card> &deck)
{
  for (int i = 0; i < deck.size() - 1; i++)
  {
    int j = i + rand() % (deck.size() - i);
    Card temp = deck.at(i);
    deck.at(i) = deck.at(j);
    deck.at(j) = temp;
  }
}

void promptPlayerCount(int &playerCount)
{
  std::cout << "how many players? minimum 2 maximum 6" << std::endl;
  std::cin >> playerCount;
  while (std::cin.fail())
  {
    std::cout << "oops, try again" << std::endl;
    std::cin.clear();
    std::cin.ignore();
    std::cin >> playerCount;
    while (playerCount < 2 || playerCount > 6)
    {
      std::cout << "Player count must be a minimum of 2 and a maximum of 6" << std::endl;
      std::cin >> playerCount;
    }
  }
  while (playerCount < 2 || playerCount > 6)
  {
    std::cout << "Player count must be a minimum of 2 and a maximum of 6" << std::endl;
    std::cin >> playerCount;
    while (std::cin.fail())
    {
      std::cout << "oops, try again" << std::endl;
      std::cin.clear();
      std::cin.ignore();
      std::cin >> playerCount;
    }
  }
}

void dealCards(std::vector<Player> &playerList, std::vector<Card> &deck)
{
  std::cout << "dealing cards to " << playerList.size() << " players" << std::endl;
  for (int i = 0; i < playerList.size(); i++)
  {
    for (int j = 0; j < 2; j++)
    {
      playerList.at(i).addCard(deck.at(deck.size() - 1));
      deck.pop_back();
    }
  }
}

void layRiver(std::vector<Card> &deck, const int &instance)
{
  static std::vector<Card> river;
  if (instance == 1)
  {
    while (river.size() > 0)
    {
      river.pop_back();
    }
  }
  std::cout << std::endl;
  switch (instance)
  {
  case 1:
    std::cout << "laying first 3 river cards..." << std::endl;
    for (int i = 0; i < 3; i++)
    {
      river.push_back(deck.at(deck.size() - 1));
      deck.pop_back();
    }
    break;
  case 2:
    std::cout << "laying fourth river card..." << std::endl;
    river.push_back(deck.at(deck.size() - 1));
    deck.pop_back();
    break;
  case 3:
    std::cout << "laying fifth river card..." << std::endl;
    river.push_back(deck.at(deck.size() - 1));
    deck.pop_back();
    break;
  }
  std::cout << "RIVER: ";
  for (int i = 0; i <= river.size() - 1; i++)
  {
    if (i == river.size() - 1)
      std::cout << river.at(i).getName() << " of " << river.at(i).getSuit().getSuitName();
    else
      std::cout << river.at(i).getName() << " of " << river.at(i).getSuit().getSuitName() << ", ";
  }
  std::cout << std::endl
            << std::endl;
}

void showPlayerCards(std::vector<Player> &playerList)
{
  for (int i = 0; i < playerList.size(); i++)
  {
    playerList.at(i).showAll();
  }
}

void setMarkersFalse(std::vector<Player> &playerList, const int &currentBetter)
{
  for (int i = 0; i < playerList.size(); i++)
  {
    playerList.at(i).setMatchStatus(false);
  }
  if (currentBetter != 99)
    playerList.at(currentBetter).setMatchStatus(true);
}

void askForBets(int &pool, std::vector<Player> &playerList, const int &instance, const int &round, const int &firstBetter)
{
  setMarkersFalse(playerList, 99);
  std::cout << "round " << round << ", instance " << instance << " of betting: " << std::endl;
  bool bettingDone = false; //needs to be original size
  std::cout << "player#" << playerList.at(firstBetter).getPlayerNumber() << " is betting first" << std::endl;
  int currentBetter = firstBetter;
  std::cout << "(b) for bet, (x) for check" << std::endl;
  char lastChoice{NULL};
  while (bettingDone == false)
  { //holy shit i think this things works lol
    //need implement hand ranking (currently just makes player 1 win)
    char choice;
    int amt;
    int raise;
    if (lastChoice)
    {
      switch (lastChoice)
      {
      case 'b':
        std::cout << "player# " << playerList.at(currentBetter).getPlayerNumber() << ", will you call (c), raise (r), or fold (f)?" << std::endl;
        if (playerList.at(currentBetter).getFirstBet() < amt)
          std::cout << "bet required is: $" << amt << " ( + $" << amt - playerList.at(currentBetter).getFirstBet() << " needed to call)" << std::endl;
        else
          std::cout << "bet required is: $" << amt << std::endl;
        if (playerList.at(currentBetter).getMoney() == 0)
        {
          std::cout << "forced check" << std::endl;
          choice = 'x';
        }
        else
          std::cin >> choice;
        if (choice == 'r')
        {
          while (playerList.at(currentBetter).getMoney() < amt && choice == 'r')
          {
            std::cout << "you dont have the funds required to raise, either call (c) or fold (f)" << std::endl;
            std::cin >> choice;
          }
        }
        break;
      case 'x':
        std::cout << "player# " << playerList.at(currentBetter).getPlayerNumber() << ", will you bet (b), or check (x)?" << std::endl;
        if (playerList.at(currentBetter).getFirstBet() < amt)
          std::cout << "bet required is: $" << amt << " ( + $" << amt - playerList.at(currentBetter).getFirstBet() << " needed to call)" << std::endl;
        else
          std::cout << "bet required is: $" << amt << std::endl;
        if (playerList.at(currentBetter).getMoney() == 0)
        {
          std::cout << "forced check" << std::endl;
          choice = 'x';
        }
        else
          std::cin >> choice;
        break;
      case 'c':
        std::cout << "player# " << playerList.at(currentBetter).getPlayerNumber() << ", will you call (c), raise (r), or fold (f)?" << std::endl;
        if (playerList.at(currentBetter).getFirstBet() < amt)
          std::cout << "bet required is: $" << amt << " ( + $" << amt - playerList.at(currentBetter).getFirstBet() << " needed to call)" << std::endl;
        else
          std::cout << "bet required is: $" << amt << std::endl;
        if (playerList.at(currentBetter).getMoney() == 0)
        {
          std::cout << "forced check" << std::endl;
          choice = 'x';
        }
        else
          std::cin >> choice;
        if (choice == 'r')
        {
          while (playerList.at(currentBetter).getMoney() < amt && choice == 'r')
          {
            std::cout << "you dont have the funds required to raise, either call (c) or fold (f)" << std::endl;
            std::cin >> choice;
          }
        }
        break;
      case 'r':
        std::cout << "player# " << playerList.at(currentBetter).getPlayerNumber() << ", will you call (c), raise (r), or fold (f)?" << std::endl;
        if (playerList.at(currentBetter).getFirstBet() < amt)
          std::cout << "bet required is: $" << amt << " ( + $" << amt - playerList.at(currentBetter).getFirstBet() << " needed to call)" << std::endl;
        else
          std::cout << "bet required is: $" << amt << std::endl;
        if (playerList.at(currentBetter).getMoney() == 0)
        {
          std::cout << "forced check" << std::endl;
          choice = 'x';
        }
        else
          std::cin >> choice;
        if (choice == 'r')
        {
          while (playerList.at(currentBetter).getMoney() < amt && choice == 'r')
          {
            std::cout << "you dont have the funds required to raise, either call (c) or fold (f)" << std::endl;
            std::cin >> choice;
          }
        }
        break;
      case 'f':
        std::cout << "player# " << playerList.at(currentBetter).getPlayerNumber() << ", will you call (c), raise (r), or fold (f)?" << std::endl;
        if (playerList.at(currentBetter).getFirstBet() < amt)
          std::cout << "bet required is: $" << amt << " ( + $" << amt - playerList.at(currentBetter).getFirstBet() << " needed to call)" << std::endl;
        else
          std::cout << "bet required is: $" << amt << std::endl;
        if (playerList.at(currentBetter).getMoney() == 0)
        {
          std::cout << "forced check" << std::endl;
          choice = 'x';
        }
        else
          std::cin >> choice;
        if (choice == 'r')
        {
          while (playerList.at(currentBetter).getMoney() < amt && choice == 'r')
          {
            std::cout << "you dont have the funds required to raise, either call (c) or fold (f)" << std::endl;
            std::cin >> choice;
          }
        }
        break;
      }
      switch (choice)
      {
      case 'b':
        std::cout << "how much do you want do bet? ($)" << std::endl;
        std::cin >> amt;
        while (amt < 1)
        {
          std::cout << "must enter at least 1 dollar to bet" << std::endl;
          std::cin >> amt;
          while (amt > playerList.at(currentBetter).getMoney())
          {
            std::cout << "bet exceeds available funds, please specify an amount to bet equal to or lower than $" << playerList.at(currentBetter).getMoney() << std::endl;
            std::cin >> amt;
          }
        }
        while (amt > playerList.at(currentBetter).getMoney())
        {
          std::cout << "bet exceeds available funds, please specify an amount to bet equal to or lower than $" << playerList.at(currentBetter).getMoney() << std::endl;
          std::cin >> amt;
          while (amt < 1)
          {
            std::cout << "must enter at least 1 dollar to bet" << std::endl;
            std::cin >> amt;
          }
        }
        pool += amt;
        playerList.at(currentBetter).withdraw(amt);
        std::cout << "pool is currently at : $" << pool << std::endl;
        setMarkersFalse(playerList, currentBetter);
        break;
      case 'x':
        std::cout << "player# " << playerList.at(currentBetter).getPlayerNumber() << " has checked." << std::endl;
        playerList.at(currentBetter).setMatchStatus(true);
        std::cout << "pool is currently at : $" << pool << std::endl;
        break;
      case 'c':
        std::cout << "player# " << playerList.at(currentBetter).getPlayerNumber() << " has called the bet of " << amt << std::endl;
        if (playerList.at(currentBetter).getFirstBet() < amt)
        {
          if (playerList.at(currentBetter).getMoney() < (amt - playerList.at(currentBetter).getFirstBet()))
          {
            pool += playerList.at(currentBetter).getMoney();
            playerList.at(currentBetter).withdraw(playerList.at(currentBetter).getMoney());
          }
          else
          {
            playerList.at(currentBetter).withdraw((amt - playerList.at(currentBetter).getFirstBet()));
            pool += (amt - playerList.at(currentBetter).getFirstBet());
          }
        }
        else
        {
          if (playerList.at(currentBetter).getMoney() < amt)
          {
            pool += playerList.at(currentBetter).getMoney();
            playerList.at(currentBetter).withdraw(playerList.at(currentBetter).getMoney());
          }
          else
          {
            playerList.at(currentBetter).withdraw(amt);
            pool += amt;
          }
        }
        playerList.at(currentBetter).setFirstBet(amt);
        playerList.at(currentBetter).setMatchStatus(true);
        std::cout << "pool is currently at : $" << pool << std::endl;
        break;
      case 'r':
        std::cout << "player# " << playerList.at(currentBetter).getPlayerNumber() << " has chosen to raise." << std::endl;
        std::cout << "how much would you like to raise by? ($)" << std::endl;
        std::cin >> raise;
        while ((raise + amt) > playerList.at(currentBetter).getMoney())
        {
          std::cout << "raise exceeds available funds, please specify an amount to bet equal to or lower than $" << (playerList.at(currentBetter).getMoney() - amt) << std::endl;
          std::cin >> raise;
        }
        amt += raise;
        pool += amt;
        playerList.at(currentBetter).setFirstBet(amt);
        std::cout << "bet has been raised by $" << raise << ", bet is now $" << amt << std::endl;
        playerList.at(currentBetter).withdraw(amt);
        setMarkersFalse(playerList, currentBetter);
        std::cout << "pool is currently at : $" << pool << std::endl;
        break;
      case 'f':
        std::cout << "player# " << playerList.at(currentBetter).getPlayerNumber() << " has folded :(" << std::endl;
        playerList.at(currentBetter).setMatchStatus(true);
        playerList.at(currentBetter).setFold(true);
        break;
      }
    }
    else
    {
      if (playerList.at(currentBetter).getMoney() == 0)
      {
        std::cout << "player# " << playerList.at(currentBetter).getPlayerNumber() << " has checked. (no funds to bet with)" << std::endl;
        choice = 'x';
      }
      else
        std::cin >> choice;
      switch (choice)
      {
      case 'b':
        std::cout << "how much do you want do bet? ($)" << std::endl;
        std::cin >> amt;
        while (amt < 1)
        {
          std::cout << "must enter at least 1 dollar to bet" << std::endl;
          std::cin >> amt;
          while (amt > playerList.at(currentBetter).getMoney())
          {
            std::cout << "bet exceeds available funds, please specify an amount to bet equal to or lower than $" << playerList.at(currentBetter).getMoney() << std::endl;
            std::cin >> amt;
          }
        }
        while (amt > playerList.at(currentBetter).getMoney())
        {
          std::cout << "bet exceeds available funds, please specify an amount to bet equal to or lower than $" << playerList.at(currentBetter).getMoney() << std::endl;
          std::cin >> amt;
          while (amt < 1)
          {
            std::cout << "must enter at least 1 dollar to bet" << std::endl;
            std::cin >> amt;
          }
        }
        pool += amt;
        playerList.at(currentBetter).withdraw(amt);
        std::cout << "pool is currently at : $" << pool << std::endl;
        playerList.at(currentBetter).setMatchStatus(true);
        playerList.at(currentBetter).setFirstBet(amt);
        break;
      case 'x':
        std::cout << "player# " << playerList.at(currentBetter).getPlayerNumber() << " has checked." << std::endl;
        amt = 0;
        playerList.at(currentBetter).setMatchStatus(true);
        std::cout << "pool is currently at : $" << pool << std::endl;
        break;
      }
    }
    lastChoice = choice;
    currentBetter++;
    currentBetter %= playerList.size();
    while (playerList.at(currentBetter).getFold() == true)
    {
      std::cout << "player# " << playerList.at(currentBetter).getPlayerNumber() << " has folded :(" << std::endl;
      currentBetter++;
      currentBetter %= playerList.size();
    }
    bettingDone = true;
    for (int i = 0; i < playerList.size(); i++)
    {
      if (playerList.at(i).getMatchStatus() == false)
      {
        if (playerList.at(i).getFold() == true)
          playerList.at(i).setMatchStatus(true);
        else
          bettingDone = false;
      }
      if (bettingDone == false)
        break;
    }
    if (bettingDone)
    {
      if (amt == 0)
        std::cout << "everyone checked, betting done for this round :)" << std::endl;
      else
        std::cout << "everyone called, betting done for this round :)" << std::endl;
    }
  }
}

void alocateWinnings(int &pool, std::vector<Player> &playerList)
{
  //determineWinner();
  std::cout << "player# " << playerList.at(0).getPlayerNumber() << " has won the pool of $" << pool << std::endl;
  playerList.at(0).setMoney(playerList.at(0).getMoney() + pool);
  pool = 0;
}

void eliminateLosers(std::vector<Player> &playerList)
{
  std::vector<Player> notLosers;
  for (int i = 0; i < playerList.size(); i++)
  {
    if (playerList.at(i).getMoney() == 0)
      std::cout << "player# " << playerList.at(i).getPlayerNumber() << " has been eliminated" << std::endl;
    else
      notLosers.push_back(playerList.at(i));
  }
  playerList.swap(notLosers);
}

void emptyPlayerHands(std::vector<Player> &playerList)
{
  for (int i = 0; i < playerList.size(); i++)
  {
    playerList.at(i).emptyHand();
  }
}

void playGame(const int &playerCount, std::vector<Card> &deck)
{
  int money;
  std::cout << "how much money will players start with?" << std::endl;
  std::cin >> money;
  std::vector<Player> playerList;
  for (int i = 0; i < playerCount; i++)
  {
    Player player(i + 1, money);
    playerList.push_back(player);
  }
  int round{0};
  while (playerList.size() > 1)
  { //while list is bigger than 1, more than 1 player remain in game
    int firstBetter = round % playerCount % playerList.size();
    round++;
    int pool{0};
    emptyPlayerHands(playerList);
    fillDeck(deck);
    shuffleDeck(deck);
    dealCards(playerList, deck);
    //ok at this point the players each hold 2 cards and they are removed from the deck :)
    showPlayerCards(playerList);
    askForBets(pool, playerList, 1, round, firstBetter);
    layRiver(deck, 1);
    //displayDeck(deck);
    askForBets(pool, playerList, 2, round, firstBetter);
    layRiver(deck, 2);
    askForBets(pool, playerList, 3, round, firstBetter);
    layRiver(deck, 3);
    askForBets(pool, playerList, 4, round, firstBetter);
    alocateWinnings(pool, playerList);
    eliminateLosers(playerList);
    for (int i = 0; i < playerList.size(); i++)
    {
      playerList.at(i).setFold(false);
    }
  }
  std::cout << "game over, winner is player# " << playerList.at(0).getPlayerNumber() << std::endl;
}

void startGame()
{
  int playerCount{0};
  std::vector<Card> deck;
  promptPlayerCount(playerCount);
  std::cout << "you chose " << playerCount << " players :)" << std::endl;
  playGame(playerCount, deck);
}

int main()
{
  srand(time(0));
  startGame();
  return 0;
}