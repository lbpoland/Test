#ifndef __CARD_BASE_H
#define __CARD_BASE_H
#define CARD_SUIT_HEARTS   1
#define CARD_SUIT_DIAMONDS 2
#define CARD_SUIT_CLUBS    3
#define CARD_SUIT_SPADES   4
#define CARD_SUIT_JOKER    5
#define CARD_NUMBER_JACK    11
#define CARD_NUMBER_QUEEN   12
#define CARD_NUMBER_KING    13
#define CARD_NUMBER_ACE     1
#define CARD_HAND_THREE         1
#define CARD_HAND_SINGLE        2
#define CARD_HAND_TWO           4
#define CARD_HAND_NO_ADORNMENTS 8
#define CARD_HAND_LETTERS       16
#ifndef CARD_BASE_NO_CLASSES
class playing_card {
   int suit;
   int number;
}
#endif
#endif