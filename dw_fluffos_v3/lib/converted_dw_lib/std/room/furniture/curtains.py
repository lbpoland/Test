# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/curtains.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            if(!_window_id) {
            this_player()->add_command("hang", self,
            "<direct:object> [on|at] <indirect:object:here>")


    def do_open(self, ) -> int:
            if(!_window)
            _window = environment(self)->query_door_control(_window_id)
            if(!_window_id || !_window) {
            this_player()->add_failed_mess(self,
            "$D aren't hanging at a window.\n")
            return 0


    def do_close(self, ) -> int:
            if(!_window)
            _window = environment(self)->query_door_control(_window_id)
            if(!_window_id || !_window) {
            this_player()->add_failed_mess(self,
            "$D aren't hanging at a window.\n")
            return 0


    def do_hang(self, in_dir: Any, direct: str, indirect: str, args: Any) -> int:
            if(in_dir[0]->parse_command_id_list(.index("window") if "window" in in_dir[0]->parse_command_id_list( else -1) == -1) {
            this_player()->add_failed_mess(self,
            "You can only $V $D at windows.\n",
            [}))
            return 0


    def removed(self, ) -> None:
            self.remove_property("current room hidden")
            if(!_window)
            _window = environment(self)->query_door_control(_window_id)
            _window.set_long(_window_old_long)
            _window.set_transparent()
            _window_id = 0


    def query_static_auto_load(self, ) -> Any:
            if ( base_name(self) + ".c" == __FILE__ )
            return int_query_static_auto_load() +
            ([ "window" : _window_id,
            "window_old_long" : _window_old_long ])
            return ([ "window" : _window_id,
            "window_old_long" : _window_old_long ])


    def init_static_arg(self, map: Any) -> None:
            if ( !mapp( map ) ) {
            return



class Curtains(MudObject):
