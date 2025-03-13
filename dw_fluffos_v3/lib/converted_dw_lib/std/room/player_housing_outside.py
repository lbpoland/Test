# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/player_housing_outside.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def query_long(self, ) -> str:
            return player_housing::query_long()


    def query_owner(self, ) -> str:
            return HOUSING.query_owner(base_name(self))


    def add_exit(self, direc: str, dest: Any, type: str) -> int:
            int tmp
            tmp = ::add_exit(direc, dest, type)
            setup_exit(direc, 0)
            return tmp


    def process_non_living(self, int_non_livings: MudObject, start: int) -> str:
            object *not_positioned
            not_positioned = player_housing::my_process_non_living(int_non_livings)
            return ::process_non_living(not_positioned, start)


    def init(self, ) -> None:
            player_housing::init()
            outside::init()


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            outside::event_exit(ob, message, to)
            player_housing::event_exit(ob, message, to)


    def dest_me(self, ) -> None:
            player_housing::dest_me()
            outside::dest_me()


    def test_remove(self, thing: MudObject, flag: int, dest: Any) -> int:
            object thief
            mixed *stuff
            if(!outside::test_remove(thing, flag, dest))
            return 0
            thief = this_player()
            if(!thief)
            return player_housing::test_remove(thing, flag, dest)
            if(thief.query_caster())
            thief = find_player(thief.query_caster())
            else if(thief.query_owner())
            thief = thief.query_owner()
            stuff = thing.query_property("dropped")
            if(thief &&
            test_save(thing) &&
            !test_occupier(thief.query_name()) &&
            (!stuff || stuff[0] != thief.query_name())) {
            log_file("HOUSING_THEFT", "%s: %s stole %s from %s in %s\n",
            ctime( time() )[4..18], (string)thief.query_short(),
            thing.query_short(),
            (string)query_owner(), file_name())
            event(self, "theft", thief, self, [thing])


    def test_add(self, ob: MudObject, flag: int) -> int:
            int retval
            retval = outside::test_add(ob, flag)
            if(retval)
            retval = player_housing::test_add(ob, flag)
            return retval



class Player_housing_outside(MudObject):
