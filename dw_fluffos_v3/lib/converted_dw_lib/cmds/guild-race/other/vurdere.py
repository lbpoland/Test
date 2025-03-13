# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/guild-race/other/vurdere.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .utilities import CLOTHING_HANDLER
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def calc_sausage(self, sausage: int, lvl: int) -> int:
            int tmp
            tmp = 99 - (lvl * 99) / 200
            if( tmp < 0 )
            tmp = 0
            return random( sausage ) * tmp / 100 - random( sausage ) * tmp / 100 +
            sausage


    def check_string(self, val: int, bon: int) -> str:
            int dist
            string s
            dist = (350 - bon) / 10
            if( dist > (val < 0 ? -val : val) )
            return " is the same as "
            if( val > 0 )
            s = "better than "
            else {
            s = "worse than "
            val -= val


    def cmd_against(self, object*from, to: MudObject) -> int:
            int i, j, k, l, arm_lvl
            object *ok, *fail
            mixed *rat, *to_ac, *zip
            arm_lvl = (int)this_player()->query_skill_bonus( SKILL )
            if(sizeof(from) + sizeof(to) > 10) {
            add_failed_mess("You cannot compare that many items at once.\n")
            return 0


    def cmd_normal(self, from: Any) -> int:
            int i, j
            object *ok, *fail
            mixed *rat, bing
            string type, *types, *zones
            ok = [})
            fail = [})
            for( i = 0; i < sizeof( from ); i++ ) {
            if( from[ i ]->query_armour() ) {
            rat = calc_ac( from[ i ] )
            for( j = 0; j < sizeof( rat ); j += 2 ) {
            bing = (rat[ j + 1 ][ 0 ] + rat[ j + 1 ][ 1 ] + rat[ j + 1 ][ 2 ]) / 3
            bing /= 5
            if( bing >= 10 ) {
            bing = 9


    def teach(self, ob: MudObject) -> int:
            if( this_player()->query_skill( SKILL ) < TEACH_LEVEL )
            return -1
            if( ob.query_skill( SKILL ) < LEARN_LEVEL )
            return -2
            ob.add_known_command( "vurdere" )
            return 1



class Vurdere(MudObject):
