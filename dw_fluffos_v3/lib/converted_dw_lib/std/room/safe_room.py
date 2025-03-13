# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/safe_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def trap_action(self, str: str) -> int:
            string st1
            if( sscanf( str,"%s %s",str,st1 ) )
            switch(str) {
            case "ambush":
            case "attack":
            case "backstab":
            case "behead":
            case "bury":
            case "cast":
            case "circle":
            case "conflagrate":
            case "crush":
            case "decompose":
            case "drag":
            case "eat":
            case "ensumpf":
            case "fade":
            case "filch":
            case "fire":
            case "fuel":
            case "guard":
            case "hedgehog":
            case "hide":
            case "hurl":
            case "iai":
            case "inhume":
            case "inpale":
            case "invoke":
            case "kill":
            case "mock":
            case "order":
            case "tempt":
            case "palm":
            case "perform":
            case "plant":
            case "pyroscipate":
            case "scathe":
            case "scribe":
            case "scry":
            case "shroud":
            case "slip":
            case "snatch":
            case "sneak":
            case "steal":
            case "recharge":
            case "rifle":
            case "throw":
            case "twist":
            case "use":
            case "ventisepelate":
            case "zap":
            case "skick":
            case "sburn":
            case "slap":
            case "spunch":
            case "berserk":
            await  this_player().send("You feel too peaceful to do that.\n")
            return 1
            default:
            return 0


    def init(self, ) -> None:
            this_player()->remove_hide_invis( "hiding" )
            clone_object( SHAD )->setup_shadow(TP)
            this_player()->command_override( (: trap_action :) )
            this_player()->add_command( "dream", self, "" )
            this_player()->add_command( "rest", self, "" )
            ::init()


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            ob.dest_shadow()


    def event_enter(self, ob: MudObject, stringy: str, stringy2: str) -> None:
            object thing
            if ( base_name( ob ) == "/d/classs/priests/summoned/dust_devil" ) {
            ob.do_leave()


    def do_rest(self, str: str) -> int:
            this_player()->adjust_hp( 4 )
            this_player()->adjust_gp( -( 2 + random( 4 ) ) )
            this_player()->adjust_social_points( -( 2 + random(8)))
            tell_object( this_player() ,
            "You rest on one of the pillows, and feel much "
            "better for it.\n")
            return 1


    def do_dream(self, str: str) -> int:
            this_player()->adjust_hp( 4 )
            this_player()->adjust_gp( -( 2 + random( 4 ) ) )
            this_player()->adjust_social_points( -( 2 + random(8)))
            tell_object( this_player(), ({
            "You dream of a world where cabbages roam free.\n",
            "You have a vision of penguin waiters serving giraffes in white leisure "
            "suits.\n",
            "You dream of imp-powered sheep leaping over fences.\n",
            "You dream uneasily of creators with cuddly teddy-bears.\n",
            "Visions of sugar-plums dance through your head.\n",
            "You count lemons as you try to get to sleep.\n"] [ random(4) ] )
            return 1


    def event_fight_in_progress(self, ob1: MudObject, ob2: MudObject) -> None:
            if ( keeper ) { tell_room ( self,
            keeper.the_short() + " hums a peaceful tune softly and calm fils the "
            "room." ); }
            ob2.stop_all_fight()
            ob1.stop_all_fight()


    def make_calm(self, blue: MudObject) -> None:
            int *enums
            int wibble
            enums = blue.effects_matching("fighting.combat")
            if ( sizeof( enums ) ) {
            foreach( wibble in enums ) { blue.delete_effect( wibble ); }
            keeper.do_command("smile "+ blue->query_name() )
            await  blue.send("You feel a lot calmer.\n")


    def stop_sneaking(self, sneaker: MudObject) -> None:
            int *enums
            int wibble
            enums = sneaker.effects_matching( "covert.sneaking" )
            if ( sizeof( enums ) ) {
            foreach( wibble in enums ) { sneaker.delete_effect( wibble ); }
            keeper.do_command("hug "+ sneaker->query_name() )
            await  sneaker.send("You feel less sneaky.\n")



class Safe_room(MudObject):
