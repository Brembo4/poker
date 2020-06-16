#include <string>
#include <iostream>
#include "Classes.h"

std::string Suit::getSuitName()
{
  return suitName;
}
int Suit::getSuitValue()
{
  return suitValue;
}
Suit::Suit(int suitValue)
    : suitValue{suitValue}
{
  switch (suitValue)
  {
  case 1:
    this->suitName = "Hearts";
    break;
  case 2:
    this->suitName = "Diamonds";
    break;
  case 3:
    this->suitName = "Spades";
    break;
  case 4:
    this->suitName = "Clubs";
    break;
  }
}
Suit Card::getSuit()
{
  return suit;
}
int Card::getValue()
{
  return intValue;
}
std::string Card::getName()
{
  return nameValue;
}
Card::Card(Suit suit, int intValue)
    : suit{suit}, intValue{intValue}
{
  switch (intValue)
  {
  case 1:
    this->nameValue = "Two";
    break;
  case 2:
    this->nameValue = "Three";
    break;
  case 3:
    this->nameValue = "Four";
    break;
  case 4:
    this->nameValue = "Five";
    break;
  case 5:
    this->nameValue = "Six";
    break;
  case 6:
    this->nameValue = "Seven";
    break;
  case 7:
    this->nameValue = "Eight";
    break;
  case 8:
    this->nameValue = "Nine";
    break;
  case 9:
    this->nameValue = "Ten";
    break;
  case 10:
    this->nameValue = "Jack";
    break;
  case 11:
    this->nameValue = "Queen";
    break;
  case 12:
    this->nameValue = "King";
    break;
  case 13:
    this->nameValue = "Ace";
    break;
  }
}
std::vector<Card> Player::getHand()
{
  return hand;
}
void Player::addCard(Card card)
{
  hand.push_back(card);
}
int Player::getPlayerNumber()
{
  return playerNumber;
}
void Player::showAll()
{
  for (int i = 0; i < hand.size(); i++)
  {
    std::cout << "player " << playerNumber << ": " << hand.at(i).getName() << " of " << hand.at(i).getSuit().getSuitName() << std::endl;
  }
}
void Player::withdraw(int amt)
{
  money -= amt;
  std::cout << "-----removed $" << amt << " from player# " << playerNumber << "'s funds ($" << money << " remaining)" << std::endl;
}
int Player::getMoney()
{
  return money;
}
void Player::setMoney(int value)
{
  money = value;
}
bool Player::getMatchStatus()
{
  return betMatched;
}
void Player::setFirstBet(int amt)
{
  firstBet = amt;
}
int Player::getFirstBet()
{
  return firstBet;
}
void Player::setMatchStatus(bool status)
{
  betMatched = status;
}
bool Player::getFold()
{
  return this->fold;
}
void Player::setFold(bool fold)
{
  this->fold = fold;
}
void Player::emptyHand() {
  while (hand.size() > 0) {
    hand.pop_back();
  }
}
Player::Player(int playerNumber, int money, bool betMatched) : playerNumber{playerNumber}, money{money}, betMatched{betMatched}
{
}