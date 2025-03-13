# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/misc/death_shadow.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def test_add(self, ob: MudObject) -> int:
            if (ob.query_property("dead usable"))
            return 1
            return 0


    def attack(self, ) -> None:


    def adjust_hp(self, ) -> None:


    def set_hp(self, ) -> None:


    def do_death(self, ) -> None:


    def setup_shadow(self, ob: MudObject) -> None:
            shadow( ob, 1 )
            my_player = ob
            cost_life = my_player.query_property( "death cost life" )
            my_player.remove_property( "death cost life" )
            resurrect_adds_life = my_player.query_property( "resurrect should add life" )
            my_player.remove_property( "resurrect should add life" )


    def attack_by(self, ob: MudObject) -> int:
            await  ob.send("This person is a ghost... You cannot attack them.\n" )
            ob.stop_fight( my_player )
            return 1


    def attack_ob(self, ob: MudObject) -> int:
            write( "Your hand passes right through it!  You are just a ghost!\n" )
            return 0


    def short(self, ) -> str:
            if ( !my_player )
            return "Death shadow"
            return "the ghost of "+my_player.short()


    def dest_death_shadow(self, ) -> None:
            destruct( self )


    def cast(self, ) -> int:
            write( "Casting spells when you are dead?\n" )
            return 1


    def do_shout(self, ) -> int:
            write( "You are dead, that is not possible.\n" )
            return 1


    def do_echo(self, ) -> int:
            write( "You are dead...\n" )
            return 1


    def do_guild_command(self, ) -> int:
            write( "You are dead!\n" )
            return 1


    def do_race_command(self, ) -> int:
            write( "You are dead!\n" )
            return 1


    def score(self, ) -> int:
            write( "You are just a disembodied spirit.  What use has a wispy thing "
            "like you have for a collection of meaningless numbers?\n" )
            return 1


    def second_life(self, ) -> None:



class Death_shadow(MudObject):
