# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/object.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._materials = []
            self.create_me = (string)this_player()->query_name()
            self.create_me = "who knows"


    def set_name(self, word: str) -> None:
            if ( query_name() && ( query_name() != "object" ) ) {
            ::set_name(word)
            return


    def query_long_details(self, arg: str, dark: int, looker: MudObject) -> str:
            string stuff
            stuff = ""
            if ( this_player()->query_see_octarine() ) {
            stuff += enchant_string()


    def replace_long_dollars(self, player: MudObject, text: str) -> str:
            if ( colour ) {
            text = replace( text, "$colour$",
            (string)CMR_HANDLER.identify_colour( colour, player ) )


    def long(self, word: str, dark: int) -> str:
            string stuff
            stuff = ::long( word, dark )
            stuff += calc_extra_look()
            stuff += query_long_details(word, dark, this_player())
            stuff = replace_long_dollars( this_player(), stuff )
            return stuff


    def query_material(self, ) -> str:
            if (sizeof(_materials)) {
            return _materials[0]


    def set_material(self, word: Any) -> None:
            if (!arrayp(word)) {
            word = [word]


    def add_material(self, material: Any) -> None:
            if (pointerp(material)) {
            _materials |= material
            } else if (stringp(material)) {
            _materials += [material]


    def set_quality(self, quality: int) -> None:
            add_property("quality", quality)


    def query_quality(self, ) -> int:
            return query_property("quality")


    def init_static_arg(self, map: Any) -> None:
            if ( !mapp( map ) ) {
            return


    def init_dynamic_arg(self, map: Any, object) -> None:
            int recycle
            if ( !mapp( map ) )
            return
            recycle = query_property("no recycling")
            if ( map[ "properties" ] )
            map_prop = map[ "properties" ]
            if (recycle)
            add_property("no recycling", recycle)
            if ( map[ "timed properties" ] ) {
            timed_properties = map[ "timed properties" ]
            reload_player_properties()


    def query_readable_message(self, player: MudObject, ignore_labels: int) -> str:
            string ret
            string bing
            object *labels
            object ob
            int *enums
            object store
            ret = ::query_readable_message(player)
            if (!ignore_labels) {
            enums = (int *)self.effects_matching( "object.label" )
            if ( !sizeof( enums ) ) {
            labels = [})
            } else {
            store = (object)self.arg_of( enums[ 0 ] )[ 0 ]
            if ( !objectp( store ) ) {
            labels = [})
            } else {
            labels = (object *)store.find_inv_match( "" )


    def query_read_short(self, player: MudObject, ignore_labels: int) -> str:
            string ret
            object *labels
            int *enums
            object store
            ret = ::query_read_short(player)
            if (!ignore_labels) {
            enums = (int *)self.effects_matching( "object.label" )
            if ( !sizeof( enums ) ) {
            labels = [})
            } else {
            store = (object)self.arg_of( enums[ 0 ] )
            if ( !objectp( store ) ) {
            labels = [})
            } else {
            labels = (object *)store.find_inv_match( "" )


    def query_help_file_directory(self, ) -> str:
            return "/doc/object/"


    def clean_up(self, inherited: int) -> int:
            if(inherited) {
            log_file("CLEANUP", "%s %s cleaned up.\n", ctime(time()),
            file_name(self))
            move("/room/rubbish")


    def dest_me(self, ) -> None:
            effects_desting()
            ::dest_me()



class Object(MudObject):

    _materials = '[]'

    create_me = '"who knows"'
