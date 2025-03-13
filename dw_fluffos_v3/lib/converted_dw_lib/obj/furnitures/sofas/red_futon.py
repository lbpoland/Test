# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/sofas/red_futon.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            folded = 0
            set_name( "futon" )
            set_short( "traditional red futon" )
            add_adjective( ["traditional", "red" } ))
            add_alias( "couch" )
            add_alias( "sofa" )
            set_long( "This red mattressed futon is made of a pad of tufted "
            "cotton batting covered with red cotton cloth, set in a "
            "lacquered oaken frame.  The frame allows the futon to rest "
            "comfortably a few inches above the ground, its hard mattress "
            "a must for those craving a little punishment combined with "
            "a good night's sleep.  It looks comfortable and is the perfect "
            "thing to have if you are into the whole minimalistic trend "
            "for your home.\n")
            set_allowed_positions(({"sitting", "lying", "kneeling", "meditating"}))
            set_allowed_room_verbs((["sitting" : "sits" ]))
            set_weight(150)
            set_value(650000)
            add_extra_look( self )


    def init(self, ) -> None:
            add_command("unfold", "<indirect:object'futon'>" )
            add_command("fold", "<indirect:object'futon'>" )
            ::init()


    def do_unfold(self, ob: MudObject) -> int:
            if(folded ) {
            add_failed_mess("$D is already folded.\n", [}) )
            return 0


    def do_fold(self, ob: MudObject) -> int:
            if(!folded) {
            add_failed_mess("$D is already folded.\n", [}) )
            return 0


    def extra_look(self, ) -> str:
            if(!folded) {
            return "The futon has been folded out into a bed.\n"



class Red_futon(MudObject):
