# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/npc/unsocial_effect.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, arg: Any, id: int) -> None:
            tell_object( player, "The spectral image of a "+arg[0]+" appears in front "
            "of you and looks sadly at you through pale eyes.  You shudder "
            "in horror as the image passes through you with tears in its "
            "eyes.  You find your yourself less able to communicate from the "
            "shock.\n")
            tell_room( environment( player ), player.the_short()+" suddenly looks "
            "straight ahead and shudders for no visible reason.\n", player )
            player.submit_ee( "reminder_mess", 20, EE_CONTINUOUS )
            player.submit_ee( 0, arg[1], EE_REMOVE )
            player.set_max_sp( 0 )


    def merge_effect(self, player: MudObject, time1: int, time2: int, id: int) -> int:
            player.submit_ee( 0, time1 + time2 - (int)player.expected_tt(),
            EE_REMOVE )
            return time1 + time2


    def end(self, player: MudObject, time: int, id: int) -> None:
            int number
            tell_object( player, "You feel you have recovered and are ready to "
            "communicate with the world again.\n")
            number= player.query_real_max_sp()
            player.adjust_max_sp( number )


    def reminder_mess(self, player: MudObject, arg: Any, id: int) -> None:
            string message
            if (!random(4))
            switch(random(2)){
            case 0 :
            message = "The spectral image of a "+arg[0]+" just like you had "
            "as a "
            "child appears in front of you.  Before you know what you are "
            "doing you strike out at the "+arg[0]+" spilling spectral blood "
            "everywhere.\n"
            break
            default :
            message = "You have a vision of yourself walking down a street "
            "when suddenly a masked "+arg[0]+" jumps out of the shadows "+
            "and cuts you into pieces with its natural weapons.\n"
            break



class Unsocial_effect(MudObject):
