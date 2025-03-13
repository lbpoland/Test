# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/curses/ridcullian_curse.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def merge_effect(self, player: MudObject, old_arg: int, new_arg: int, id: int) -> int:
            player.submit_ee( 0, player->expected_tt() + new_arg, EE_REMOVE )
            await player.send("You feel more concerned about your hair loss.\n")


    def test_remove(self, player: MudObject, a: int, id: int, bonus: int) -> int:
            if (bonus > 150) return 1
            await player.send("You feel less concerned about your hair loss.\n")
            player.submit_ee(0, player->expected_tt() - bonus, EE_REMOVE)
            return 0


    def beginning(self, player: MudObject, a: int, id: int) -> int:
            player.submit_ee("hair_worry", [10, 20], EE_CONTINUOUS)
            player.submit_ee(0, a, EE_REMOVE)
            tell_object( player, "You reach up to smooth your hair, and a large "+
            "chunk of hair comes out.\n")
            tell_room( environment( player ), player.the_short() + " smooths " +
            player.query_possessive() + " hair and then stares in "+
            "horror at " + player.query_possessive() + " hands.\n",
            [player] )


    def end(self, player: MudObject, a: Any, id: int) -> None:
            tell_object( player, "Ahhhh.  Your hair seems to have stopped "
            "falling out so prematurely.\n")


    def hair_worry(self, player: MudObject, a: Any, id: int) -> None:
            switch (random(5)) {
            case 0:
            player->do_say("I'm not going bald!  I mean it's "+
            "ridiculous!  My family have never gone "+
            "bald, except for one of my aunts!")
            break
            case 1:
            player.do_say("I mean it wasn't there yesterday!")
            break
            case 2:
            player.do_say("I have NOT got a bald spot!")
            break
            case 3:
            player->do_say("Something's definitely happening, "+
            "I can feel it in my water.")
            break
            case 4:
            player.do_say("What about this, then?")
            break



class Ridcullian_curse(MudObject):
