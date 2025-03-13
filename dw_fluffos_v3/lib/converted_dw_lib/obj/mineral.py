# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/mineral.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def long(self, words: str, dark: int) -> str:
            return replace( ::long( words, dark ), "$mineral$",
            (string)HANDLER.identify_material( mineral, this_player(), 1 ) )


    def init(self, ) -> None:
            ::init()
            this_player()->add_command( "pulverise", self,
            "<direct:object> {with|using} <indirect:object>" )
            this_player()->add_command( "chip", self,
            "<direct:object> {with|using} <indirect:object>" )
            this_player()->add_command( "smash", self,
            "<direct:object> {with|using} <indirect:object>" )
            this_player()->add_command( "sprinkle", self,
            "<direct:object:me> [on] <indirect:object>" )
            this_player()->add_command( "sprinkle", self,
            "<direct:object:me>" )


    def do_eat(self, ) -> int:
            if ( (string)this_player()->query_race_ob() != "/std/races/troll" ) {
            this_player()->add_failed_mess( self,
            "What do you think you are, a troll?\n", [}) )
            return 0


    def check_tool(self, tools: MudObject, needed: str) -> int:
            string word
            if ( sizeof( tools ) > 1 ) {
            write( "You only need to use one tool at a time.\n" )
            return 0


    def do_pulverise(self, tools: MudObject) -> int:
            string material_adjective
            if ( !check_tool( tools, ["hammer"] ) )
            return 0
            if ( query_continuous() ) {
            write( "The "+ (string)HANDLER->identify_material( mineral,
            this_player(), 0 ) +" has already been pulverised.\n" )
            return 0


    def do_chip(self, tools: MudObject) -> int:
            object chip
            if ( query_continuous() )
            return 0
            if ( !check_tool( tools, ["pick", "pickaxe", "hammer"] ) )
            return 0
            if ( query_weight() == 1 ) {
            write( "This piece of "+ (string)HANDLER->identify_material( mineral,
            this_player(), 0 ) +" is already a chip.\n" )
            return 0


    def do_smash(self, tools: MudObject) -> int:
            int i, j, largest, number, size
            object debris, remains
            if ( query_continuous() )
            return 0
            if ( !check_tool( tools, ["pick", "pickaxe"] ) )
            return 0
            if ( query_weight() < ROCK / 2 ) {
            write( "This piece of "+ (string)HANDLER->identify_material( mineral,
            this_player(), 0 ) +" is too small to smash.\n" )
            return 0


    def do_sprinkle(self, obs: MudObject) -> int:
            if (!query_continuous())
            return notify_fail(
            "You should pulverise the stuff before you sprinkle it.\n")
            if (!sizeof(obs)) {
            obs=[environment(this_player())]
            this_player()->add_succeeded_mess(self,
            "$N $V $D everywhere.\n",[}))
            } else {
            this_player()->add_succeeded_mess(self,
            "$N $V $D on $I.\n",[obs[0]])


    def init_static_arg(self, map: Any) -> None:
            if ( map[ "::" ] )
            ::init_static_arg( map[ "::" ] )
            if ( !undefinedp( map[ "mineral" ] ) )
            mineral = map[ "mineral" ]
            set_decay_speed(0)


    def set_decay_level(self, level: int) -> None:
            ::set_decay_level( 0 )
            return



class Mineral(MudObject):
