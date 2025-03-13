# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/npc/surface_decorator.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):
            add_help_file("/doc/object/surface_decorator")
            add_enter_commands("#check_domain")


    def init(self, ) -> None:
            ::init()
            this_player()->add_command( "ask", self, "<direct:object> to "
            "fit the <string'surface'> with <string'decor'>",
            (: do_ask($4[1], $4[2])  :) )
            this_player()->add_command( "list", self, "goods from "
            "<direct:object>" )
            this_player()->add_command( "hire", self, "<direct:object>")


    def do_list(self, ) -> int:
            int i
            string thing
            i=1
            if( !sizeof( fitted_surfaces ) ) {
            init_command( responses[8], 1 )
            return 1


    def do_hire(self, ) -> int:
            this_player()->add_succeeded_mess( self, "$N ask$s $D about "
            + self.query_possessive() + " services.\n", [}) )
            if( !this_player()->query_visible( self ) ) {
            init_command( responses[10], 1 )
            return 1


    def do_ask(self, surface: str, decor: str) -> int:
            string long, allowed, place
            int fee, can_do
            object where
            can_do = 0
            foreach( allowed in allowed_surfaces ) {
            if( strsrch( surface, allowed ) != -1 ) {
            can_do = 1


    def finish_work(self, surface: str, long: str, where: MudObject) -> None:
            do_command(":finishes his work.")
            if( employer ) {
            employer.add_follower(self)


    def check_domain(self, ) -> None:
            string allowed, here
            int ok
            here = file_name( environment( self ) )
            ok = 0
            foreach( allowed in allowed_domains ) {
            if( strsrch( here, allowed ) != -1 ) {
            ok = 1


    def add_fitted_surface(self, short: str, long: str, cost: int) -> None:
            fitted_surfaces[ short ] = [long, cost]


    def remove_fitted_surface(self, short: str) -> None:
            map_delete( fitted_surfaces, short )


    def remove_all_fitted_surfaces(self, ) -> None:
            fitted_surfaces = ([ ])


    def add_allowed_surface(self, surface: str) -> None:
            if( allowed_surfaces .index( surface) if  surface in allowed_surfaces  else -1 == -1 ) {
            allowed_surfaces += [surface]


    def add_allowed_domain(self, domain: str) -> None:
            if( allowed_domains .index( domain) if  domain in allowed_domains  else -1 == -1 ) {
            allowed_domains += [domain]


    def set_responses(self, the_responses: str) -> None:
            if( sizeof(the_responses) != sizeof(responses) ) {
            return 0


    def set_under_construction_mess(self, mess: str) -> None:
            under_construction_mess = mess


    def set_work_time(self, time: int) -> None:
            work_time = time


    def set_employer(self, player: MudObject) -> None:
            employer = player



class Surface_decorator(MudObject):
