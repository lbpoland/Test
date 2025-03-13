# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/misc/offler_shadow.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup_shadow(self, thing: MudObject) -> None:
            shadow( thing, 1 )
            player = thing


    def adjust_hp(self, number: int, thing: MudObject, weapon: MudObject, attack: str) -> int:
            if ( number > 0 )
            return (int)player.adjust_hp( number, thing, weapon, attack )
            else
            return (int)player.query_hp()


    def set_hp(self, number: int, thing: MudObject) -> int:
            int current
            current = (int)player.query_hp()
            if ( number > current )
            return (int)player.set_hp( number, thing )
            else
            return current


    def attack_by(self, thing: MudObject) -> int:
            await  thing.send((string)player.the_short() +
            " is prevented from fighting by Offler.\n" )
            thing.stop_fight( self )
            return 0


    def attack_ob(self, thing: MudObject) -> int:
            await  player.send("You are prevented from fighting by Offler.\n" )
            thing.stop_fight( self )
            return 0


    def do_ambushed(self, ) -> None:
            write( "You suddenly see a terrifying image of a huge crocodile!\n" )
            this_player()->run_away()


    def no_offense(self, ) -> int:
            write( "You are prevented from offensive actions by Offler.\n" )
            return 1


    def cast(self, ) -> int:
            write( "You are about to start when Offler stops you.\n" )
            return 1



class Offler_shadow(MudObject):
