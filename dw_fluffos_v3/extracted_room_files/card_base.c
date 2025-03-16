# File: /lib/std/room/furniture/games/card_base.c

#include <room/card_base.h>
#define CARD_NUM_MAX CARD_NUMBER_KING
int is_card_red(class playing_card card);
class playing_card* make_deck(int number_of_decks,
                              int number_of_jokers) {
   class playing_card* deck;
   class playing_card card;
   int i;
   int suit;
   int num;
   deck = ({ });
   for (i = 0; i < number_of_decks; i++) {
      for (suit = CARD_SUIT_HEARTS; suit <= CARD_SUIT_SPADES; suit++) {
         for (num = 1; num <= CARD_NUM_MAX; num++) {
            card = new(class playing_card);
            card->suit = suit;
            card->number = num;
            deck += ({ card });
         }
      }
   }
   for (i = 0; i < number_of_jokers; i++) {
      card = new(class playing_card);
      card->suit = CARD_SUIT_JOKER;
      deck += ({ card });
   }
   return deck;
}
class playing_card* shuffle_deck(class playing_card* deck) {
   class playing_card* new_deck;
   int pos;
   int i;
   for (i = 0; i < 2; i++) {
      new_deck = ({ });
      while (sizeof(deck)) {
         pos = random(sizeof(deck));
         new_deck += deck[pos..pos];
         deck = deck[0..pos - 1] + deck[pos+1..];
      }
      deck = new_deck;
   }
   return deck;
}
string query_suit_letter(int suit) {
   switch (suit) {
   case CARD_SUIT_SPADES :
      return "S";
      break;
   case CARD_SUIT_HEARTS :
      return "H";
      break;
   case CARD_SUIT_DIAMONDS :
      return "D";
      break;
   case CARD_SUIT_CLUBS :
      return "C";
      break;
   case CARD_SUIT_JOKER :
      return "J";
   }
}
string query_card_string(class playing_card card) {
   string ret;
   string colour;
   if (card->suit == CARD_SUIT_JOKER) {
      return "*J*";
   }
   ret = query_suit_letter(card->suit) + "%^RESET%^";
   if (is_card_red(card)) {
      colour = "%^BOLD%^%^RED%^";
   } else {
      colour = "%^BOLD%^";
   }
   if (card->number > 10 || card->number == CARD_NUMBER_ACE) {
      switch (card->number) {
      case CARD_NUMBER_JACK :
         ret = colour + "J " + ret;
         break;
      case CARD_NUMBER_QUEEN :
         ret = colour + "Q " + ret;
         break;
      case CARD_NUMBER_KING :
         ret = colour + "K " + ret;
         break;
      case CARD_NUMBER_ACE :
         ret = colour + "A " + ret;
         break;
      }
   } else {
      ret = sprintf("%s%-2d%s", colour, card->number, ret);
   }
   return ret + "%^RESET%^";
}
int is_card_red(class playing_card card) {
   return card->suit == CARD_SUIT_HEARTS || card->suit == CARD_SUIT_DIAMONDS;
}
int is_card_black(class playing_card card) {
   return card->suit == CARD_SUIT_SPADES || card->suit == CARD_SUIT_CLUBS;
}
int is_card_joker(class playing_card card) {
   return card->suit == CARD_SUIT_JOKER;
}
string* query_card_three(class playing_card card) {
   string* lines;
   if (is_card_red(card)) {
      lines = allocate(3, "%^BOLD%^%^RED%^");
   } else {
      lines = allocate(3, "%^BOLD%^");
   }
   switch (card->suit) {
   case CARD_SUIT_HEARTS :
      lines[0] += "H  %^RESET%^";
      lines[2] += "  H%^RESET%^";
      break;
   case CARD_SUIT_DIAMONDS :
      lines[0] += "D  %^RESET%^";
      lines[2] += "  D%^RESET%^";
      break;
   case CARD_SUIT_CLUBS :
      lines[0] += "C  %^RESET%^";
      lines[2] += "  C%^RESET%^";
      break;
   case CARD_SUIT_SPADES :
      lines[0] += "S  %^RESET%^";
      lines[2] += "  S%^RESET%^";
      break;
   case CARD_SUIT_JOKER :
      lines[0] += "J *%^RESET%^";
      lines[1] += " O %^RESET%^";
      lines[2] += "* K%^RESET%^";
      return lines;
   }
   if (card->number <= 10 && card->number != CARD_NUMBER_ACE) {
      if (card->number == 10) {
         lines[1] += " 10%^RESET%^";
      } else {
         lines[1] += " " + card->number + " %^RESET%^";
      }
   } else {
      switch (card->number) {
      case CARD_NUMBER_KING :
         lines[1] += " K %^RESET%^";
         break;
      case CARD_NUMBER_QUEEN :
         lines[1] += " Q %^RESET%^";
         break;
      case CARD_NUMBER_JACK :
         lines[1] += " J %^RESET%^";
         break;
      case CARD_NUMBER_ACE :
         lines[1] += " A %^RESET%^";
         break;
      }
   }
   return lines;
}
string* query_card_two(class playing_card card) {
   string* lines;
   lines = allocate(2);
   switch (card->suit) {
   case CARD_SUIT_HEARTS :
      lines[0] = "H ";
      break;
   case CARD_SUIT_DIAMONDS :
      lines[0] = "D ";
      break;
   case CARD_SUIT_CLUBS :
      lines[0] = "C ";
      break;
   case CARD_SUIT_SPADES :
      lines[0] = "S ";
      break;
   case CARD_SUIT_JOKER :
      lines[0] = "J*";
      lines[1] = "*O";
      return lines;
   }
   if (card->number <= 10 && card->number != CARD_NUMBER_ACE) {
      lines[1] = sprintf("%2d", card->number);
   } else {
      switch (card->number) {
      case CARD_NUMBER_KING :
         lines[1] = " K";
         break;
      case CARD_NUMBER_QUEEN :
         lines[1] = " Q";
         break;
      case CARD_NUMBER_JACK :
         lines[1] = " J";
         break;
      case CARD_NUMBER_ACE :
         lines[1] = " A";
         break;
      }
   }
   return lines;
}
string query_hand_string(class playing_card* hand, int flags, int cols) {
   string hand_str;
   int i;
   int j;
   int width;
   int start_pos;
   string top;
   string line;
   string start;
   string end;
   string start_space;
   string end_space;
   mixed card_str;
   if (!sizeof(hand)) {
      return "No cards\n";
   }
   hand_str = "";
   if (!(flags & CARD_HAND_NO_ADORNMENTS)) {
      if (flags & CARD_HAND_THREE ||
          flags & CARD_HAND_SINGLE) {
         top = "+---+";
         width = 5;
      } else {
         top = "+--+";
         width = 4;
      }
      start = "|";
      end = "|";
      start_space = " ";
      end_space = " ";
   } else {
      top = 0;
      line = "";
      start = " ";
      end = " ";
      start_space = " ";
      end_space = " ";
      if (flags & CARD_HAND_THREE ||
          flags & CARD_HAND_SINGLE) {
         width = 3;
      } else {
         width = 2;
      }
   }
   start_pos = 0;
   if (flags & CARD_HAND_THREE) {
      card_str = map(hand, (: query_card_three :));
   } else if (flags & CARD_HAND_SINGLE) {
      card_str = map(hand, (: ({ query_card_string($1) }) :));
   } else {
      card_str = map(hand, (: query_card_two :));
   }
   while (start_pos < sizeof(hand)) {
      if (top) {
         line = "";
         for (i = 0; i + start_pos < sizeof(hand) && (i + 1) * width < cols; i++) {
            line += top;
         }
         line += "\n";
      }
      if (flags & CARD_HAND_LETTERS) {
         for (i = 0; i + start_pos < sizeof(hand) && (i + 1) * width < cols; i++) {
            if (flags & CARD_HAND_THREE) {
               hand_str += start_space + sprintf(" %c ", 'A' + i + start_pos) + end_space;
            } else {
               hand_str += start_space + sprintf("%c ", 'A' + i + start_pos) + end_space;
            }
         }
      }
      hand_str += "\n" + line;
      for (j = 0; j < sizeof(card_str[0]); j++) {
         for (i = 0; i + start_pos < sizeof(card_str) && (i + 1) * width < cols; i++) {
            hand_str += start + (card_str[i + start_pos][j]) + end;
         }
         hand_str += "\n";
      }
      hand_str += line;
      start_pos += cols / width;
   }
   return hand_str;
}
private int compare_cards(class playing_card card1, class playing_card card2,
                          int flags) {
   if (card1->suit == card2->suit ||
       (flags & 2)) {
      if (!(flags & 1)) {
         return card1->number - card2->number;
      }
      if (card1->number == CARD_NUMBER_ACE) {
         return 1;
      }
      if (card2->number == CARD_NUMBER_ACE) {
         return -1;
      }
      return card1->number - card2->number;
   }
   return card1->suit - card2->suit;
}
class playing_card* sort_cards(class playing_card* deck, int flags) {
   return sort_array(deck,
                (: compare_cards($1, $2, $(flags)) :));
}