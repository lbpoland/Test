# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/guild-race/gp.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def cmd(self, ) -> int:
            int i, gp, max_gp, other_gp
            gp = (int)this_player()->query_gp()
            max_gp = (int)this_player()->query_max_gp()
            write( "You have "+ gp +" ("+ max_gp +") class points.\n" )
            for ( i = 0; i < sizeof( STD_SKILLS ); i += SKILL_ARR_SIZE ) {
            other_gp = (int)this_player()->query_skill_bonus( STD_SKILLS[ i ]
            +".points" ) + 50
            if ( other_gp >= max_gp ) {
            write( "* All of your class points can be used for "+
            STD_SKILLS[ i ] +" commands.\n" )
            continue



class Gp(MudObject):
