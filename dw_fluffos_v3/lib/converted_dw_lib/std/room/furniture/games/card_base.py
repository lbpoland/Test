# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/games/card_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def is_card_red(self, playing_card: Any) -> int:
            class playing_card* make_deck(int number_of_decks,
            int number_of_jokers) {
            class playing_card* deck
            class playing_card card
            int i
            int suit
            int num
            deck = [})
            for (i = 0; i < number_of_decks; i++) {
            for (suit = CARD_SUIT_HEARTS; suit <= CARD_SUIT_SPADES; suit++) {
            for (num = 1; num <= CARD_NUM_MAX; num++) {
            card = new(class playing_card)
            card->suit = suit
            card->number = num
            deck += [card]


    def query_suit_letter(self, suit: int) -> str:
            switch (suit) {
            case CARD_SUIT_SPADES :
            return "S"
            break
            case CARD_SUIT_HEARTS :
            return "H"
            break
            case CARD_SUIT_DIAMONDS :
            return "D"
            break
            case CARD_SUIT_CLUBS :
            return "C"
            break
            case CARD_SUIT_JOKER :
            return "J"


    def query_card_string(self, playing_card: Any) -> str:
            string ret
            string colour
            if (card->suit == CARD_SUIT_JOKER) {
            return "*J*"


    def is_card_red(self, playing_card: Any) -> int:
            return card->suit == CARD_SUIT_HEARTS || card->suit == CARD_SUIT_DIAMONDS


    def is_card_black(self, playing_card: Any) -> int:
            return card->suit == CARD_SUIT_SPADES || card->suit == CARD_SUIT_CLUBS


    def is_card_joker(self, playing_card: Any) -> int:
            return card->suit == CARD_SUIT_JOKER


    def query_hand_string(self, playing_card: Any, flags: int, cols: int) -> str:
            string hand_str
            int i
            int j
            int width
            int start_pos
            string top
            string line
            string start
            string end
            string start_space
            string end_space
            mixed card_str
            if (!sizeof(hand)) {
            return "No cards\n"



class Card_base(MudObject):
