#include <iostream>
#include <ctime>
 // Configure project's include path to
// also contain ${workspaceFolder}/include
#include <ac_int.h>
#include <ac_channel.h>

typedef ac_int<4,false> Card;

class BlackJackPlayer{
private:
  // Internal state
  ac_int<5,false> cardsCounter;
  ac_int<3,false> cardsDrawn;
  ac_int<1,false> roundInProgress;
public:
  // Constructor - initialize internal state
  BlackJackPlayer(){
    cardsCounter = 0;
    cardsDrawn = 0;
    roundInProgress = 0;
  }
  // Top-level interface
  void draw(ac_channel<Card> &in_card, bool &end_round, bool &win){
    if (in_card.available(1)){
      Card new_card = in_card.read();
      if (roundInProgress==0){
        // If last round ended but there are cards available, start a new round
        cardsCounter = (new_card==1) ? (Card)11 : new_card;
        cardsDrawn = 1;
        roundInProgress = 1;
        std::cout << "New round, 1 card and sum=" << cardsCounter << ". ";
      } else {
        // If there is an ongoing round, draw another card
        cardsCounter += (new_card==1) ? (Card)11 : new_card;
        cardsDrawn += 1;
        std::cout << cardsDrawn <<" cards and sum=" << cardsCounter << ". ";
        // Check whether the new card caused a win, a defeat, or neither
        if (cardsCounter>21){
          roundInProgress = 0;
          if (cardsDrawn==2){
            // Player got 2 aces in the first 2 cards - victory
            win = 1;
          } else {
            // Player is busted - defeat
            win = 0;
          }
          std::cout << "Game ended, win=" << win;
        } else if (cardsCounter==21 || cardsDrawn==5){
           // Player has a BlackJack - victory, or
          // Player is not burned after 5 rounds - victory 
          roundInProgress = 0;
          win = 1;
          std::cout << "Game ended, win=" << win;
        }
      }
    } else {
      std::cout << "No action taken. ";
    }
    // Always assigned to the internal state
    end_round = !roundInProgress;
  }
};

class BlackJackDealer{
private:
  // Internal state
  Card deck[4][13];
  ac_int<1,false> roundInProgress;
public:
  // Constructor - initialize internal state
  BlackJackDealer(){
    // A full deck of 52 cards
    for (int i=0; i<4; i++){
      for (int j=0; j<13; j++){
        deck[i][j] = 1;
      }
    }
    roundInProgress = 0;
  }
  // Top-level interface
  void deal(bool &end_round, ac_channel<Card> &out_card){
    if (end_round && roundInProgress){
      // Restore deck
      for (int i=0; i<4; i++){
        for (int j=0; j<13; j++){
          deck[i][j] = 1;
        }
      }
      // Empty card buffer
      while (out_card.available(1)){
        Card discard = out_card.read();
      }
      std::cout << "Previous game ended, reseting the table";
    } else {
      unsigned short int suit = rand() % 4;
      unsigned short int rank = rand() % 13;
      if (deck[suit][rank]){
        deck[suit][rank] = 0;
        Card next_card = (rank>9) ? 10 : rank+1;
        out_card.write(next_card);
        std::cout << "Dealing a new card:(" << suit+1 << "," << rank+1 << "). ";
      } else {
        std::cout << "No action taken. ";
      }
    }
    // Always assigned to the external state
    roundInProgress = !end_round;
  }
};

int main(){
  // Initialize random seed
  srand(time(NULL));
  // Initialize game of BlackJack
  BlackJackDealer dealer;
  BlackJackPlayer player;
  ac_channel<Card> cardStream;
  bool end_round;
  bool win;
  // Number of rounds
  const int rounds = 5;
  for (int i=2; i<=rounds<<1; ){
    do{
      std::cout << "Hand " << (i>>1) << std::endl;
      std::cout << "Dealer side: ";
      dealer.deal(end_round, cardStream);
      std::cout << std::endl << "Player side: ";
      player.draw(cardStream, end_round, win);
      std::cout << std::endl;
    }while(!end_round);
    i = i+1;
  }
}