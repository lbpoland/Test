# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/stop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, word: str) -> Any:
            object *atts
            switch( word ) {
            case "debate" :
            case "debating" :
            this_player()->interrupt_debate()
            break
            case "spell" :
            this_player()->interrupt_spell()
            break
            case "ritual" :
            this_player()->interrupt_ritual()
            break
            case "fight" :
            case "fighting" :
            atts = this_player()->query_attacker_list()
            if ( !sizeof( atts ) ) {
            write( "You are not fighting anyone.\n" )
            return 1


    def stop_fight(self, who: MudObject) -> None:
            object *atts, ob
            if ( !who )
            return
            atts = who.query_attacker_list()
            atts -= [0]
            tmp = who
            if(atts == [}))
            return
            tell_object( who, "You stop fighting "+
            query_multiple_short( map_array( atts,
            (: $1.query_property( "dead" ) ? (string)$1.a_short() + " (dead anyway)" : $1 :) ) ) +".\n" )
            foreach(ob in atts)
            who.stop_fight(ob)



class Stop(MudObject):
