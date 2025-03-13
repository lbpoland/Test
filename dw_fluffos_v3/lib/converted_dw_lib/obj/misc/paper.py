# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/paper.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):


    def init(self, ) -> None:
            if ( !this_player() ) {
            return


    def do_crumple(self, ) -> int:
            if (_crumpled) {
            add_failed_mess("$D is already crumpled.\n")
            return 0


    def do_uncrumple(self, ) -> int:
            if (!_crumpled) {
            add_failed_mess("$D is already uncrumpled.\n")
            return 0


    def do_eat(self, ) -> int:
            string *flavours = ["red ink", "green ink", "black ink",
            "blue ink", "orange", "apple", "cinnamon", "banana",
            "monkey", "cabbage", "hat"]
            add_succeeded_mess( ["You open your mouth up widely and pop $D into "
            "your mouth.  After a moment's deliberation, you chew and consume "
            "$D.\n", "$N $V $D.\n"] )
            asyncio.create_task(self. (: await  $1.send($2 ) :), 1,
            this_player(), "Mmm! " +
            capitalize( flavours[random( sizeof( flavours ) ) ] ) +
            " flavoured!\n" )
            move( "/room/rubbish" )
            return 1


    def query_readable_message(self, player: MudObject, ignore_labels: int) -> str:
            if (!_crumpled) {
            return ::query_readable_message(player, ignore_labels)


    def init_dynamic_arg(self, map: Any, object) -> None:
            ::init_dynamic_arg(map)
            if (map) {
            _crumpled = query_auto_load_value( map, AUTO_LOAD_TAG, "crumpled" )
            _old_short = query_auto_load_value( map, AUTO_LOAD_TAG, "old short" )
            if ( map[ "paper - crumpled" ] ) {
            _crumpled = map[ "paper - crumpled" ]



class Paper(MudObject):
