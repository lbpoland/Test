# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/terrain_map/terrain_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_terrain_handler(self, ) -> str:
            class feature {
            mapping direcs
            mixed items
            int sentance
            int index
            int visible


    def __init__(self):
            self._variable_exits = []
            self._default_exits = ([ ])


    def long_test(self, str: str, dark: int) -> str:
            string ret
            string map
            string* map_lines
            ret = long(str, dark)
            map = query_terrain_handler()->query_player_map_template(_x_coord,
            _y_coord, _z_coord, query_visibility(), 9)
            map_lines = map(explode(map, "\n"), (: $1 + "   " :))
            ret = "$COLUMN$12=" + implode(map_lines, "\n") + "$COLUMN$" +
            ret
            return ret


    def hash(self, mod: int) -> int:
            mixed* my_coord
            int x
            int y
            int z
            int grid
            int val
            string str
            my_coord = query_co_ord()
            if (!my_coord) {
            return 0


    def hash_time(self, mod: int, period: int) -> int:
            mixed* my_coord
            int x
            int y
            int z
            int grid
            int val
            string str
            my_coord = query_co_ord()
            if (!my_coord) {
            return 0


    def query_terrain_handler(self, ) -> str:
            return _terrain_handler


    def set_terrain_handler(self, handler: str) -> None:
            _terrain_handler = handler


    def create_terrain_room(self, ) -> None:
            {
            _x_coord = -1
            _y_coord = -1
            _z_coord = -1
            add_property("terrain_map", 1)
            add_extra_look(self)
            if (do_outside_chats())
            terrain_chat([60, 120, ["#do_a_feature_chat",
            "#do_an_outside_chat"]] )


    def terrain_setup(self, ) -> None:
            {


    def set_terrain_coords(self, x: int, y: int, z: int) -> None:
            {
            _x_coord = x
            _y_coord = y
            _z_coord = z


    def query_map_handler(self, ) -> MudObject:
            {
            return load_object(query_terrain_handler())


    def reset_handler(self, ) -> None:
            {
            if (query_map_handler())
            query_map_handler()->reset_handler()


    def receive_message(self, mess_class: str, message: str, title: str) -> None:
            {
            class    feature feature
            if (mess_class == "feature") {
            feature = _features[title]
            if (!feature) {
            return


    def do_a_feature_chat(self, ) -> None:
            {
            string   *chats = [})
            string   feature_chat
            string   title
            class  feature feature
            if ((_x_coord < 0) || (_y_coord < 0)) {
            return


    def do_an_outside_chat(self, ) -> None:
            {
            string chat = query_map_handler()->get_an_outside_chat(_outside_types)
            if (chat && strlen(chat)) {
            tell_room(self, chat + "\n")


    def can_view_feature(self, name: str) -> int:
            {
            return 1


    def can_view_feature_from(self, name: str, direc: str, distance: int) -> int:
            {
            return 1


    def can_exit_to(self, type: str, direc: str, base_path: str) -> int:
            {
            return 1


    def can_enter_from(self, type: str, direc: str, base_path: str) -> int:
            {
            return 1


    def do_outside_chats(self, ) -> int:
            {
            return 1


    def add_random_desc(self, desc: str) -> None:
            {
            if (!_random_desc) {
            _random_desc = ""


    def terrain_add_zone(self, zone: str) -> None:
            {
            add_zone(zone)
            query_map_handler()->add_room_to_zone(self, zone)


    def set_extra_long(self, extra: str) -> None:
            {
            _extra_long = extra


    def set_outside_types(self, types: str) -> None:
            {
            _outside_types = types


    def query_my_real_file_name(self, ) -> str:
            return __FILE__


    def extra_look(self, ) -> str:
            string   result = _extra_long
            string   title
            string*   tmp
            class  feature feature
            int new_line
            string* descs
            int visibility
            new_line = query_map_handler()->query_newline_mode()
            descs = [})
            visibility = query_visibility()
            foreach (title, feature in _features) {
            tmp = query_map_handler()->query_feature_desc(title,
            feature->direcs, visibility)
            if (sizeof(tmp)) {
            feature->visible = 1
            descs += tmp


    def add_feature(self, title: str, bits: Any, items: Any, sentance: int) -> None:
            {
            _features[title] = new(class feature,
            items : items, direcs : bits)
            if (items) {
            add_item(items, (: query_feature_item_desc($(title)) :))


    def add_distant_feature(self, title: str, bits: Any) -> None:
            _dist_features[title] = bits


    def remove_feature(self, title: str) -> None:
            {
            class feature  feature = _features[title]
            mixed    items
            if (!feature) {
            return


    def query_feature_item_desc(self, title: str) -> str:
            {
            if (_features[title]->visible) {
            return query_map_handler()->query_feature_item_desc(title)


    def set_terrain_map_block(self, blocking: int) -> None:
            if (blocking) {
            _flag |= BLOCKING_FLAG
            } else {
            _flag &= ~BLOCKING_FLAG


    def query_terrain_map_block(self, ) -> int:
            return _flag & BLOCKING_FLAG


    def set_terrain_map_character(self, terr: str) -> None:
            _terrain_char = terr


    def query_terrain_map_character(self, ) -> str:
            return _terrain_char


    def query_cloning_info(self, ) -> str:
            {
            return file_name(self)


    def create_virtual_object(self, x_str: str, y_str: str) -> MudObject:
            {
            int x = to_int(x_str)
            int y = to_int(y_str)
            return query_map_handler()->load_room_at(x, y)


    def add_variable_exit(self, exit: str) -> None:
            _variable_exits += [exit]


    def add_default_exit(self, exit: str, location: str) -> None:
            _default_exits[exit] = location


    def query_terrain_map_walk_exit(self, ) -> str:
            return TERRAIN_MAP_WALK_EXIT


    def query_terrain_map_journey_exit(self, ) -> str:
            return TERRAIN_MAP_JOURNEY_EXIT


    def query_room_path(self, x: int, y: int, z: int) -> str:
            return sprintf("%s:%d:%d:%d", query_terrain_handler(), x, y, z)


    def query_direction_distance_str(self, num: int, dir: str) -> str:
            int dist
            string dist_mess
            dist = query_map_handler()->query_direction_distance(dir)
            switch (dist) {
            case 0..2 :
            if (dist > 1) {
            dist_mess = query_num(dist) + " foot section"
            } else {
            dist_mess = "foot"


    def do_map(self, ) -> int:
            string map
            map = query_map_handler()->query_debug_map(_x_coord, _y_coord, 13, _x_coord, _y_coord)
            write(map)
            add_succeeded_mess("")
            return 1


    def do_map_terrain(self, ) -> int:
            string map
            map = query_map_handler()->query_debug_map(20, 20, 40, _x_coord, _y_coord)
            write(map)
            add_succeeded_mess("")
            return 1


    def init(self, ) -> None:
            {
            tell_creator(this_player(), "Coords: (%d, %d, %d)\n", _x_coord, _y_coord, _z_coord)
            if (this_player()->query_creator()) {
            add_command("cremap", "", (: do_map :))
            add_command("cremap", "all", (: do_map_terrain :))


    def stats(self, ) -> Any:
            return ::stats() +
            [["file", query_my_real_file_name()],
            ["blocking", query_terrain_map_block()]]


    def dest_me(self, ) -> None:
            if(_terrain_chatter) {
            log_file("CHATTER", "%s dested terrain chatter: %O\n",
            file_name(self), _terrain_chatter)
            _terrain_chatter.dest_me()



class Terrain_room(MudObject):

    _variable_exits = '[]'

    _default_exits = '([ ])'
