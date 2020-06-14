#ifndef _CLASSES_H_
#define _CLASSES_H_
#include <string>
#include <vector>

class Suit
{
private:
  std::string suitName;
  int suitValue;

public:
  std::string getSuitName();
  int getSuitValue();
  Suit(int suitValue);
};

class Card
{
private:
  Suit suit;
  int intValue;
  std::string nameValue;

public:
  Suit getSuit();
  int getValue();
  std::string getName();
  Card(Suit suit, int intValue);
};

class Player
{
private:
  bool fold{false};
  int firstBet{INT_MAX};
  int money;
  int playerNumber;
  bool betMatched;
  std::vector<Card> hand;

public:
  bool getFold();
  void setFold(bool fold);
  void setFirstBet(int amt);
  int getFirstBet();
  void setMoney(int money);
  int getMoney();
  void withdraw(int amt);
  int getPlayerNumber();
  bool getMatchStatus();
  void setMatchStatus(bool status);
  std::vector<Card> getHand();
  void showAll();
  void addCard(Card card);
  void emptyHand();
  Player(int playerNumber, int money, bool betMatched = false);
};

#endif