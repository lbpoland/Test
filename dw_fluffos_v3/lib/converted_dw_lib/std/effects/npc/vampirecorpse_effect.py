# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/npc/vampirecorpse_effect.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, corpse: MudObject, args: Any) -> None:
            corpse.add_extra_look( self )
            corpse.submit_ee( "corpse_action", 10, EE_CONTINUOUS )


    def end(self, corpse: MudObject, args: Any) -> None:
            object ob, vampire
            tell_room( environment(corpse), "The corpse's eyes snap open, and a "
            "vicious grin spreads across its face.  It rises upwards without "
            "bothering to push away from the ground, standing upright, its eyes "
            "flashing.  You notice that the fangs of the corpse look considerably "
            "longer than they used to.\n" )
            vampire = clone_object( "/d/ram/chars/Uberwald/corpse_vampire" )
            vampire.setup_vampire( args[0], args[1] )
            vampire.move( environment( corpse ), vampire.the_short() + " glances "
            "down at " + vampire.query_objective() + "self and grimaces.  " +
            capitalize( vampire.query_pronoun() ) + " waves one arm and is "
            "instantly clothed in more fitting garments.\n"  )
            vampire.do_command( "grin viciously" )
            corpse.clear_armours()
            foreach( ob in all_inventory( corpse ) ) {
            ob.move( environment( corpse ) )


    def corpse_action(self, corpse: MudObject, args: Any) -> None:
            int rate
            object *stuff
            stuff = all_inventory (corpse)
            rate = (int) (corpse.query_decay())
            if( sizeof( stuff ) ) {
            tell_room( environment(corpse), corpse.one_short() + " twitches "
            "slightly.\n" )
            if (rate < 20) {
            tell_room( environment(corpse), corpse.one_short() + " seems to "
            "arch its back, and a faint gasp comes from its mouth.\n" )
            corpse.submit_ee( 0, 1, EE_REMOVE )


    def extra_look(self, corpse: MudObject, args: Any) -> str:
            return "It seems to be twitching slightly, almost as if it's still "
            "alive.  You probably shouldn't get too close.\n"



class Vampirecorpse_effect(MudObject):
