# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/misc/harry_shadow.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup_shadow(self, thing: MudObject, word: str) -> None:
            shadow( thing, 1 )
            player = thing
            protector = word
            protecting = 1
            asyncio.create_task(self. "dest_harry_shadow", 60 * 20 )


    def zap_harry_shadow(self, ) -> None:
            protecting = 0
            await  player.send("You lose "+ protector +"'s protection.\n" )
            asyncio.create_task(self. "dest_harry_shadow", 1 )


    def adjust_hp(self, number: int, thing: MudObject, weapon: MudObject, attack: str) -> int:
            if ( ( number > 0 ) || !protecting ||
            !thing || !pk_check(thing, player ) || player == this_player() )
            return (int)player.adjust_hp( number, thing, weapon, attack )
            return (int)player.query_hp()


    def set_hp(self, number: int, thing: MudObject) -> int:
            int current
            current = (int)player.query_hp()
            if ( ( number > current ) || !protecting || !thing || !thing.query_player_killer() )
            return (int)player.set_hp( number, thing )
            return current


    def attack_by(self, thing: MudObject) -> int:
            if ( !protecting || !thing.query_player_killer( ) )
            return (int)player.attack_by( thing )
            await  thing.send((string)player.the_short() +
            " are protected from combat by "+ protector +".\n" )
            tell_object( player, "You are protected from combat by "+
            protector +".\n" )
            thing.stop_fight( player )
            return 0


    def attack_ob(self, thing: MudObject) -> int:
            if ( protecting )
            zap_harry_shadow()
            return (int)player.attack_ob( thing )


    def do_ambushed(self, ) -> None:
            write( protector +" stops you from harming "+
            (string)player.the_short() +".\n" )
            tell_object( player, protector +" stops "+
            (string)this_player()->the_short() +" from harming you.\n" )


    def no_offense(self, ) -> int:
            if ( protecting )
            zap_harry_shadow()
            return (int)player.no_offense()


    def query_player_killer(self, ) -> int:
            return 0


    def command_shadowed(self, verb: str, args: str) -> int:
            if ( ["cast", "scathe", "perform"] .index( verb) if  verb in ["cast", "scathe", "perform"]  else -1 == -1 )
            return (int)player.command_shadowed( verb, args )
            if ( protecting )
            zap_harry_shadow()
            return (int)player.command_shadowed( verb, args )



class Harry_shadow(MudObject):
