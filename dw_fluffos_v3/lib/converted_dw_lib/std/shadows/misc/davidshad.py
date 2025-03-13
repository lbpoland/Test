# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/misc/davidshad.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup_shadow(self, thing: MudObject) -> None:
            shadow( thing, 1 )
            player = thing


    def run_away(self, ) -> None:
            await player.send("You feel too peaceful to run away.\n")


    def pk_check(self, thing1: Any, thing2: Any, off_line: int) -> int:
            return 1


    def adjust_hp(self, number: int, attacker: MudObject) -> None:
            if(player.query_attacker_list()) {
            foreach(attacker in player.query_attacker_list()) {
            attacker.stop_fight(player)
            player.stop_fight(attacker)


    def adjust_gp(self, number: int) -> None:
            if ( number < 0 )
            return player.adjust_gp( number )
            return


    def attack_by(self, ob: MudObject) -> int:
            ob.stop_fight(player)
            player.stop_fight(ob)
            return 1



class Davidshad(MudObject):
