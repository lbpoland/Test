# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/property_tracker.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._invalid_properties = ['team', 'ctf_deaths', 'ctf_shared']
            self._property_funcs = ([ ])


    def __init__(self):
            self._invalid_properties = ['team', 'ctf_deaths', 'ctf_shared']
            self._property_funcs = ([ ])


    def remove_invalid_property(self, property: str) -> int:
            #ifdef LORD_ONLY
            if ( !master()->query_lord( previous_object( -1 ) ) ) {
            tell_creator( this_player(1), "Get a Lord to add your property for "
            "you.\n" )
            return 0


    def save_file(self, ) -> None:
            unguarded( (: save_object, "/save/property_tracker" :) )


    def reset_data(self, ) -> None:
            unguarded( (: rm, "/save/property_tracker.o" :) )


    def convert_no_score(self, property: str, who: MudObject, data: Any) -> None:
            if ( property != "no_score" )
            return
            if ( data ) {
            who.remove_property( property )
            who.add_property( "no score", 1 )


    def remove_warmth(self, property: str, who: MudObject, data: Any) -> int:
            if ( property != "warmth" ) {
            return 1



class Property_tracker(MudObject):

    _invalid_properties = "['team', 'ctf_deaths', 'ctf_shared']"

    _property_funcs = '([ ])'
