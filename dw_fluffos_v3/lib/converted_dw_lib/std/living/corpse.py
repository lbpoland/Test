# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/living/corpse.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def alter_corpse(self, corpse: MudObject, weapon: MudObject, attack: str) -> int:
            object head
            string *heads
            string behead_message = ""
            if (!attack) attack = "attack"
            switch (attack) {
            case "behead" :
            heads =
            self.query_race_ob( self )->query_possible_bits( "head" )
            if (sizeof(heads) == 0)
            break
            head = corpse.make_bit(heads[random(sizeof(heads))] )
            head.move( environment( corpse ) )
            switch(random(6)) {
            case 0 : behead_message = head.a_short() +
            " drops onto the ground and rolls head over, well, head "
            "for a bit before coming to a rest.\n"
            break
            case 1 : behead_message = head.a_short() +
            " sails through the air in a graceful arc before landing "
            "with a very soggy *squish*.\n"
            break
            case 2 : behead_message = head.a_short() +
            " quivers a bit as it remains in place, perched atop its owner's "
            "corpse for a moment, then falls to pieces.\n"
            break
            case 3 : behead_message = head.a_short() +
            " tips off to the left to hang by a small bit of flesh, before "
            "gravity has something to say about the matter and pulls it "
            "completely off the corpse, landing with a small bounce.\n"
            break
            case 4 : behead_message = head.a_short() +
            " slides off its owner's corpse, upends, and lands upside "
            "down, helping to keep some of the blood from spilling.\n"
            break
            case 5 : behead_message = head.a_short() +
            " drops onto the ground like a ball, *bouncy* *bouncy*.\n"
            break
            case 6 :
            case 7 :
            case 8 :
            case 9 :
            default : behead_message = "oops, the mushrooms have turned.\n"


    def make_corpse(self, ) -> MudObject:
            int i
            object corpse, *armour, *weapons, race
            race = find_object(self.query_race_ob())
            if(race && function_exists("make_corpse", race))
            return race.make_corpse()
            corpse = clone_object( "/obj/corpse" )
            corpse.set_owner( 0, self )
            corpse.set_ownership( (string)self.query_name() )
            if ( self.query_property( "player" ) ) {
            corpse.add_property( "player", 1 )



class Corpse(MudObject):
