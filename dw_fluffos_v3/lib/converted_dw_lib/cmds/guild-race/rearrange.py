# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/guild-race/rearrange.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_save(self, ) -> None:
            int player, here
            player = this_player()->query_real_con() +
            this_player()->query_real_dex() +
            this_player()->query_real_str() +
            this_player()->query_real_int() +
            this_player()->query_real_wis()
            here = ME_CON + ME_DEX + ME_STR + ME_INT + ME_WIS
            if (player != here) {
            log_file("BAD_REARRANGE",
            sprintf("%s: %s had %d now has %d\n",
            ctime(time()),
            this_player()->query_name(),
            player, here))
            PLAYERINFO_HANDLER->add_entry(
            self,
            this_player()->query_name(),
            "misc",
            sprintf("rearranged from %d points to %d points", player, here),
            0)


    def display_stats(self, ) -> None:
            printf( "Con: %d Dex: %d Int: %d Str: %d Wis: %d Pool: %d\n",
            ME_CON, ME_DEX, ME_INT, ME_STR, ME_WIS, POOL )


    def get_stat_bit(self, word: str) -> int:
            int num
            string stat
            word = lower_case( word )
            if ( word == "save" ) {
            if ( POOL ) {
            write( "WARNING: You still have points left in your pool that "
            "could be used to make your character more powerful. If you "
            "leave these unspent now, you will not be able to get them again later. "
            "Are you sure you want to save? [y/n] " )
            input_to( "get_check" )
            return 1


    def get_check(self, word: str) -> int:
            word = lower_case( word )
            if ( word[ 0 ] != 'y' ) {
            write( "Going back to stat entering.\n" )
            return get_stat_bit( "" )


    def cmd(self, ) -> int:
            write( "Rearranging stats.\n\n" )
            points[ this_player() ] = ([ ])
            ME_CON = (int)this_player()->query_real_con()
            ME_DEX = (int)this_player()->query_real_dex()
            ME_INT = (int)this_player()->query_real_int()
            ME_STR = (int)this_player()->query_real_str()
            ME_WIS = (int)this_player()->query_real_wis()
            POOL = 0
            if ( ME_CON > 8)  {
            POOL += ME_CON - 8
            ME_CON = 8


    def clean_up(self, ) -> int:
            if (sizeof(points))
            return 1
            ::clean_up()


    def reset(self, ) -> None:
            if (sizeof(points))
            return
            ::reset()


    def query_name(self, ) -> str:
            {
            return "Rearrange Command"



class Rearrange(MudObject):
