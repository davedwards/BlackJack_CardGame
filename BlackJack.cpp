// BlackJack.cpp : 

#include <iostream>
#include <vector>
#include <iterator>
#include <memory>
#include <random>
#include <ctime>

enum Rank {
    ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
};

enum Suit {
    HEARTS, DIAMONDS, CLUBS, SPADES
};

class Card {
public:
    Card(Rank rank, Suit suit) : rank_(rank), suit_(suit) {}

    Rank getRank() const { return rank_; }
    Suit getSuit() const { return suit_; }

private:
    Rank rank_;
    Suit suit_;
};

class Deck {
public:
    Deck() {
        for (int suit = HEARTS; suit <= SPADES; ++suit) {
            for (int rank = ACE; rank <= KING; ++rank) {
                cards_.push_back(std::make_unique<Card>(static_cast<Rank>(rank), static_cast<Suit>(suit)));
            }
        }
    }

    void shuffleDeck() {
        std::random_device rd;
        std::mt19937 g(rd());
        shuffle(cards_.begin(), cards_.end(), g);
    }

    std::unique_ptr<Card> drawCard() {
        if (cards_.empty()) {
            return nullptr;
        }
        std::unique_ptr<Card> card = std::move(cards_.back());
        cards_.pop_back();
        return card;
    }

public:
    std::vector<std::unique_ptr<Card> > cards_;
};

class Player {
public:
    void addCard(std::unique_ptr<Card> card){
        hand_.push_back(std::move(card));
    }

    int getHandValue() const {
        int value = 0;
        int aces = 0;
        for (const auto& card : hand_) {
            int cardValue = card->getRank();
            if (cardValue >= 10) {
                cardValue = 10;
            }
            else if (cardValue == ACE) {
                aces++;
                cardValue = 11;
            }
            value += cardValue;
        }

        while (value > 21 && aces > 0)
        {
            value -= 10;
            aces--;
        }
        return value;
    }
public:
    std::vector<std::unique_ptr<Card> > hand_;
};

int main(int argc, char* argv[])
{
    std::cout << "Hello Black Jack!\n";
    Deck deck;
    deck.shuffleDeck();

    Player player;
    Player dealer;

    player.addCard(deck.drawCard());
    player.addCard(deck.drawCard());

    dealer.addCard(deck.drawCard());
    dealer.addCard(deck.drawCard());

    std::cout << "Player hand value: " << player.getHandValue() << std::endl;
    std::cout << "Dealer hand value: " << dealer.getHandValue() << std::endl;

    // Inspect hands and deck
    /*std::vector<std::unique_ptr<Card> >::iterator it;
    std::cout << "Player: " << player.hand_.size() << ": ";
    for (it = player.hand_.begin(); it < player.hand_.end(); it++) {
        std::cout << it->get()->getRank() << ": " << it->get()->getSuit() << ", ";
    }
    std::cout << std::endl;
    std::cout << "Dealer: " << dealer.hand_.size() << ": ";
    for (it = dealer.hand_.begin(); it < dealer.hand_.end(); it++) {
        std::cout << it->get()->getRank() << ": " << it->get()->getSuit() << ", ";
    }
    std::cout << std::endl;
    std::cout << "Deck: " << deck.cards_.size() << ": ";
    for (it = deck.cards_.begin(); it < deck.cards_.end(); it++) {
        std::cout << *it << ": " << it->get()->getRank() << ": " << it->get()->getSuit() << std::endl;
    }*/

    return 0;
}
