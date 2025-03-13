# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/pub.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._menu_items = ([ ])
            self._menu_aliases = ([ ])
            self._menu_header = "The menu reads:"
            self._display_header = 1
            self._menu_subheadings = ['Appetisers', 'Main Courses', 'Desserts']
            self._display_subheadings = 1
            self._menu_object = clone_object( PUB_MENU_FILE )
            self._counter = make_counter()


    def __init__(self):
            self._menu_items = ([ ])
            self._menu_aliases = ([ ])
            self._menu_header = "The menu reads:"
            self._display_header = 1
            self._menu_subheadings = ['Appetisers', 'Main Courses', 'Desserts']
            self._display_subheadings = 1
            self._menu_object = clone_object( PUB_MENU_FILE )
            self._counter = make_counter()


    def init(self, ) -> None:
            this_player()->add_command( "buy", self, "<string>" )
            this_player()->add_command( "buy", self,
            "<string> for <indirect:living:here>" )
            this_player()->add_command( "order", self, "<string>",
            (: do_buy( $1, $2, $3, $4 ) :) )
            this_player()->add_command( "order", self,
            "<string> for <indirect:living:here>",
            (: do_buy( $1, $2, $3, $4 ) :) )


    def query_pub(self, ) -> int:
            return 1


    def set_language(self, language: str) -> None:
            _language = language


    def query_language(self, ) -> str:
            return _language


    def remove_menu_item(self, name: str) -> int:
            if( !_menu_items[name] ) {
            return 0


    def string_menu(self, items: str) -> str:
            int loop
            string str, place
            str = ""
            place = self.query_property( "place" )
            if( !place || ( place == "" ) ) {
            place = "default"


    def string_menu_of_type(self, type: int) -> str:
            string str
            string *items
            items = query_items_of_type( type )
            if( !sizeof(items) ) {
            return ""


    def read(self, ) -> str:
            string ret
            ret = "\n"
            if( _display_header ) {
            ret += _menu_header + "\n"


    def set_display_header(self, value: int) -> None:
            _display_header = value


    def query_display_header(self, ) -> int:
            return _display_header


    def set_menu_header(self, header: str) -> None:
            _menu_header = header


    def query_menu_header(self, ) -> str:
            return _menu_header


    def set_display_subheadings(self, value: int) -> None:
            _display_subheadings = value


    def query_display_subheadings(self, ) -> int:
            return _display_subheadings


    def set_menu_subheadings(self, subheading: int, text: str) -> None:
            _menu_subheadings[ subheading ] = text


    def add_menu_alias(self, alias: Any, actual: str) -> None:
            string bing
            if (arrayp(alias)) {
            foreach (bing in alias) {
            add_menu_alias(bing, actual)


    def add_menu_aliases(self, aliases: str, actual: str) -> None:
            string alias
            foreach( alias in aliases ) {
            add_menu_alias( alias, actual )


    def remove_menu_alias(self, alias: str) -> int:
            if( !_menu_aliases[alias] ) {
            return 0


    def set_no_standard_alias(self, flag: int) -> None:
            no_standard_alias = flag


    def query_no_standard_alias(self, ) -> int:
            return no_standard_alias


    def create_real_object(self, name: str) -> MudObject:
            object item, container
            if( _menu_items[name]->container ) {
            container = self->create_container(
            _menu_items[name]->container )
            if( !container ) {
            container = clone_object( _menu_items[name]->container )


    def do_buy(self, obs: MudObject, dir: str, indir: str, args: Any) -> int:
            int value, cost
            string str, place
            object person, thing
            object *succeededpeople, *deadpeople, *failedpeople, *poorpeople
            succeededpeople = [})
            deadpeople = [})
            failedpeople = [})
            poorpeople = [})
            str = args[0]
            if( this_player()->query_property( "dead" ) ) {
            add_failed_mess( "How can you expect to buy " + str + " when you're "
            "dead?\n" )
            return 0


    def dest_me(self, ) -> None:
            if( _menu_object ) {
            _menu_object.dest_me()


    def make_counter(self, ) -> MudObject:
            object ob
            ob = clone_object( PUB_COUNTER_FILE )
            add_hidden_object( ob )
            return ob


    def query_counter(self, ) -> MudObject:
            return _counter


    def query_menu(self, ) -> MudObject:
            return _menu_object



class Pub(MudObject):

    _menu_items = '([ ])'

    _menu_aliases = '([ ])'

    _menu_header = '"The menu reads:"'

    _display_header = 1

    _menu_subheadings = "['Appetisers', 'Main Courses', 'Desserts']"

    _display_subheadings = 1

    _menu_object = 'clone_object( PUB_MENU_FILE )'

    _counter = 'make_counter()'
