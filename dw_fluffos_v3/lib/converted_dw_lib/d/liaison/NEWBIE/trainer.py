# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/trainer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_language( "general" )
            basic_setup( "human", "warrior", 100 )
            set_gender( 1 )
            ARMOURY.request_item("leather jerkin", 30)->move( self )
            ARMOURY.request_item("leather breeches", 30)->move( self )
            ARMOURY.request_item("hard leather boots", 30)->move( self )
            init_equip()


    def whichone(self, name: str) -> None:
            switch(name) {
            case "xrazzicaz":
            set_name( "xrazzicaz" )
            add_alias( "xraz" )
            add_property( "determinate", "" )
            set_short( "Xrazzicaz" )
            set_long( "This is the former Warriors' Guild dummy.  After being replaced by "
            "the newer mechanical dummy, Xrazzicaz decided to stay on as an "
            "instructor.\n")
            break
            case "zazzifraz":
            set_name( "zazzifraz" )
            add_alias( "zazz" )
            add_property( "determinate", "" )
            set_short( "Zazzifraz" )
            set_long( "This is Xrazzicaz' brother, a former Warriors' Guild dummy.  After "
            "being replaced by the newer mechanical dummy, Zazzifraz, like "
            "his brother, decided to stay on as an instructor.\n")
            break
            case "john":
            set_name( "john" )
            add_property( "determinate", "" )
            set_short( "John" )
            set_long( "This is Xrazzicaz' other brother, John.  He was the Warriors' "
            "Guild dummy in Ohulan Cutash until he was replaced by a "
            "mechanical dummy.  Like Xrazzicaz and Zazzifraz he got a "
            "job teaching after retirement.\n")


    def attack_by(self, thing: MudObject) -> int:
            write(self.the_short() + " glares at you before swiftly knocking "
            "you to the ground.\n")
            self.stop_fight(thing)
            thing.stop_fight(self)
            return 0


    def attack_ob(self, thing: MudObject) -> int:
            self.stop_fight(thing)
            thing.stop_fight(self)
            return 0


    def init(self, ) -> None:
            if(!this_player()) {
            return


    def do_greeting(self, ) -> None:
            string str
            if(!sizeof(greeters)) {
            return


    def stop_them(self, attacker: MudObject, dummy: MudObject) -> None:
            await  attacker.send(one_short() +" stops you attacking "+
            (string)dummy.the_short() +".\n" )
            tell_room( environment(), one_short() +" stops "+
            (string)attacker.the_short() +" attacking "+
            (string)dummy.the_short() +".\n", attacker )
            attacker.stop_fight( dummy )
            dummy.stop_all_fight()



class Trainer(MudObject):
