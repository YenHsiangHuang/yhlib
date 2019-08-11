#ifndef DECK_OF_CARDS_H
#define DECK_OF_CARDS_H
#include <vector>
#include <memory>   // smart pointer
#include <utility>  // swap
using namespace std;


//#define DEBUG  // Uncomment to enable debugging

#ifdef DEBUG
#define dbg_printf(...) printf(__VA_ARGS__)
#else
#define dbg_printf(...)
#endif

enum Suit { Spade, Heart, Diamond, Club };

class Card
{
public:
    int faceVal;
    Suit suit;

    Card(int v, Suit s) : faceVal(v), suit(s) {};

};

class Player
{
public:
    int score = 0;
    vector< shared_ptr< Card > > hand;

    int addCard(shared_ptr< Card > card);
    bool isBusted();

private:
    int updateScore();
    int updateScore(shared_ptr< Card > newCard);
};

class Deck
{
public:
    short int nCard;
    vector< shared_ptr< Card > > card;

    Deck();

    shared_ptr< Card > deal();
    bool deal(Player& player);
    void shuffle();
};


#endif
