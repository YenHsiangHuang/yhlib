#include <vector>
#include <memory>   // smart pointer
#include <utility>  // swap
#include "deckofcards.hpp"
using namespace std;

// ****************************************************************************
Deck::Deck() {
    nCard = 52;
    card.clear();
    card.resize(nCard);
    for (int i = 0; i <= 12; i++) card[13*0+i] = make_shared<Card> (i+1, Spade);
    for (int i = 0; i <= 12; i++) card[13*1+i] = make_shared<Card> (i+1, Heart);
    for (int i = 0; i <= 12; i++) card[13*2+i] = make_shared<Card> (i+1, Diamond);
    for (int i = 0; i <= 12; i++) card[13*3+i] = make_shared<Card> (i+1, Club);
}

shared_ptr<Card> Deck::deal() {
    if (card.size() == 0) return nullptr;
    shared_ptr<Card> tmp = card.back();
    card.pop_back();
    dbg_printf("deal %d\n", tmp->faceVal);
    return tmp;
}

bool Deck::deal(Player& player) {
    auto tmp = deal();
    if (tmp) {
        player.addCard(tmp);
        return true;
    }
    return false;
}

void Deck::shuffle() {
    for (int i = 0; i < nCard; i++) swap(card[i], card[rand()%nCard]);
}

// ****************************************************************************

int Player::addCard(shared_ptr<Card> newCard) {
    hand.push_back(newCard);
    return updateScore(newCard);
}

bool Player::isBusted() {
    return score > 21;
}

int Player::updateScore() {
    score = 0;
    int nAce = 0;
    for (auto& card : hand) {
        if      (card->faceVal  > 9) score += 10;
        else if (card->faceVal != 1) score += card->faceVal;
        else                         nAce++;
    }

    if (nAce <= 0) return score;

    score += 11*nAce;
    for (int i = 0; i < nAce; i++) {
        if (score <= 21) return score;
        score -= 10;
    }
    return score;
}

int Player::updateScore(shared_ptr<Card> newCard) {
    if (newCard->faceVal == 1) return updateScore();
    if (newCard->faceVal  > 9) score += 10;
    else                       score += newCard->faceVal;

    return score;
}

// ****************************************************************************
