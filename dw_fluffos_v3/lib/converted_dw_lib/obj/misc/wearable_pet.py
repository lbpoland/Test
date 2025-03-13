# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/wearable_pet.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def expand_mon_string(self, str: Any) -> None:
            object room
            string *args, *stuff
            if ( functionp( str ) ) {
            evaluate( str, self )


    def check_anyone_here(self, ) -> int:
            object holder, *people
            if(!(::check_anyone_here()))
            if ( living(holder = environment(self)) ) {
            if(environment(holder) &&
            sizeof(people = all_inventory(environment(holder))))
            if(sizeof(filter(people, (: userp($1) :))))
            return 1
            else
            return 0


    def __init__(self):


    def long(self, str: str, dark: int) -> str:
            return monster::long(str, dark)


    def init_dynamic_arg(self, map: Any) -> None:
            wearable::init_dynamic_arg(map)
            monster::init_dynamic_arg(map)


    def init_static_arg(self, map: Any) -> None:
            wearable::init_static_arg(map)
            monster::init_static_arg(map)


    def query_static_auto_load(self, ) -> Any:
            wearable::query_static_auto_load() +
            monster::query_static_auto_load()


    def query_value(self, ) -> int:
            return query_base_value()


    def stats(self, ) -> Any:
            return wearable::stats() + monster::stats()


    def break_me(self, ) -> None:
            do_death()


    def cond_string(self, ) -> str:
            health_string()


    def adjust_cond(self, i: int) -> int:
            adjust_hp( i )


    def set_max_hp(self, number: int) -> int:
            set_max_cond(number)
            set_cond(number)
            set_damage_chance( 15 )
            set_lowest_cond(1)
            return ::set_max_hp(number)



class Wearable_pet(MudObject):
