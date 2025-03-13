# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/inherit/one_armed_bandit_inherit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init(self, ) -> None:
            this_player()->add_command( "slot", self,
            _coin_short + " into <direct:object>", (: do_slot() :) )
            this_player()->add_command( "pull", self,
            "lever on <direct:object>", (: do_pull_lever() :) )
            this_player()->add_command( "read", self,
            "dial on <direct:object>", (: do_read_dial() :) )


    def set_coin_type(self, coin: str) -> int:
            if( MONEY_HAND.query_valid_types(.index( coin) if  coin in MONEY_HAND.query_valid_types( else -1 ) == -1 )
            return 0
            _coin = coin
            _coin_short = MONEY_HAND.query_aliases_for( coin )[0]
            _coin_pl = MONEY_HAND.query_main_plural_for( coin )
            return 1


    def set_chances(self, c1: int, c2: int, c3: int, c4: int, c5: int) -> int:
            if( !( c1 > 0 && c2 > 0 && c3 > 0 && c4 > 0 && c5 > 0 ) )
            return 0
            _chances = [c1, ( c1 + c2 ), ( c1 + c2 + c3 ), ( c1 + c2 + c3 + c4 ),
            ( c1 + c2 + c3 + c4 + c5 )]
            return 1


    def set_prizes(self, p1: int, p2: int, p3: int, p4: int, p5: int, jackpot: int) -> int:
            if( !( p1 > 1 && p2 > 1 && p3 > 1 && p4 > 1 && p5 > 1 && jackpot > 1 ) ||
            ( jackpot <= p1 || jackpot <= p2 || jackpot <= p3 ||
            jackpot <= p4 || jackpot <= p5 ) )
            return 0
            _prizes = ({p1, p2, p3, p4, p5, jackpot})
            return 1


    def do_slot(self, ) -> int:
            if( this_player(.index( _coin) if  _coin in this_player( else -1->query_money_array() ) == -1 ) {
            this_player()->add_failed_mess( self,
            "You need " + add_a( _coin ) + " to play.\n", [}) )
            return 0


    def do_pull_lever(self, ) -> int:
            if( _busy == 0 ) {
            this_player()->add_failed_mess( self,
            "You must put a coin in the slot before you can play.\n", [}) )
            return 0


    def rollem(self, player: MudObject) -> None:
            int a1, a2, a3, c
            int adj1 = random( 10 ),
            adj2 = random( 10 ),
            adj3 = random( 10 )
            c = random( _chances[4] )
            if( c < _chances[0] )
            a1 = 0
            else if( c < _chances[1] )
            a1 = 1
            else if( c < _chances[2] )
            a1 = 2
            else if( c < _chances[3] )
            a1 = 3
            else
            a1 = 4
            c = random( _chances[4] )
            if( c < _chances[0] )
            a2 = 0
            else if( c < _chances[1] )
            a2 = 1
            else if( c < _chances[2] )
            a2 = 2
            else if( c < _chances[3] )
            a2 = 3
            else
            a2 = 4
            c = random( _chances[4] )
            if( c < _chances[0] )
            a3 = 0
            else if( c < _chances[1] )
            a3 = 1
            else if( c < _chances[2] )
            a3 = 2
            else if( c < _chances[3] )
            a3 = 3
            else
            a3 = 4
            tell_object( player,
            "The windows now show these pictures :\n\n"
            "        " + adject[ adj1 ] + " " + animal[ a1 ] +
            "    " + adject[ adj2 ] + " " + animal[ a2 ] +
            "    " + adject[ adj3 ] + " "+animal[ a3 ] + "\n\n" )
            if( a1 == a2 && a1 == a3 ) {
            if( adj1 == adj2 && adj1 == adj3 ) {
            tell_object( player,
            "WOW!!  A triple " + adject[ adj1 ] + " " + animal[ a1 ] +
            "!!  You really hit the jackpot this time!\n\n"
            "Whistles and bells start sounding like crazy, the whole " +
            self.short() +  " glows with flashing lights.  There "
            "is a loud tingling as " + _prizes[5] + " " +
            MONEY_HAND.query_plural_for( _coin ) + " drop into the tray "
            "of " + my_short() + ".  Slightly stunned you quickly scoop "
            "it up and cackle with delight.\n" )
            tell_room( environment( self ),
            "Whistles and bells start sounding and " + my_short() +
            " starts to flash with coloured lights.  Someone must have "
            "won the jackpot...lucky buggers.  As you watch some coins "
            "drop into the tray at the bottom of " + my_short() + ", " +
            player.one_short() + " snatches it up and cackles with "
            "delight.\n", ({player}) )
            player.adjust_money( _prizes[5] ,_coin )
            self.adjust_money( -(_prizes[ 5 ]) )
            _busy = 0
            return


    def query_chances(self, ) -> List[int]:
            int* tmp = [})
            tmp += [_chances[0]]
            tmp += [_chances[1] - _chances[0]]
            tmp += [_chances[2] - _chances[1]]
            tmp += [_chances[3] - _chances[2]]
            tmp += [_chances[4] - _chances[3]]
            return tmp


    def query_prizes(self, ) -> List[int]:
            return _prizes


    def query_coin_type(self, ) -> str:
            return _coin


    def my_short(self, ) -> str:
            return self.the_short()


    def do_read_dial(self, ) -> int:
            string tmp =
            "Stake        : 1 " + _coin_pl + "\n"
            "3x Albatross : " + _prizes[0] + " " + _coin_pl + "\n"
            "3x Frog      : " + _prizes[1] + " " + _coin_pl + "\n"
            "3x Hippo     : " + _prizes[2] + " " + _coin_pl + "\n"
            "3x Turtle    : " + _prizes[3] + " " + _coin_pl + "\n"
            "3x Cabbage   : " + _prizes[4] + " " + _coin_pl + "\n"
            "JACKPOT      : " + _prizes[5] + " " + _coin_pl + "\n"
            this_player()->add_succeeded_mess( self,
            ({tmp, "$N read$s the dial on $D.\n"}), [}) )
            return 1



class One_armed_bandit_inherit(MudObject):
