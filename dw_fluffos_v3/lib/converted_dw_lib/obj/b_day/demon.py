# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/b_day/demon.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {
            set_name("demon")
            set_short("origami demon")
            add_adjective("tiny")
            add_adjective("pink")
            add_adjective("paper")
            add_adjective("origami")
            set_main_plural("origami demons")
            add_plural("demons")
            set_long("This is a tiny, pink, paper demon. Looking closely you see "
            "that it has been made by someone with a black belt in "
            "Origami!\n")
            set_race("demon")
            set_level(1)
            line = 1


    def set_owner(self, person_name: str) -> None:
            {
            owner = find_living(lower_case(person_name))
            owner_name = person_name


    def do_the_act(self, i: int) -> None:
            {
            string line_to_act
            if(i >= sizeof(act_lines)) {
            dest_me()
            return


    def attack_by(self, thing: MudObject) -> None:
            if( !thing) return
            if( environment( thing ) != environment() ) return
            self->stop_fight (thing)
            thing->stop_fight (self)
            init_command("say Meanie!  Shame on you!  I shall finish what I "
            "started and then I shall be off.  You don't really "
            "deserve this, you know.", 1)
            return



class Demon(MudObject):
