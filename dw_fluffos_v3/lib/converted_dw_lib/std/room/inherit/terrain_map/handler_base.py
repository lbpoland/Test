# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/terrain_map/handler_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_real_coordinates_no_inform(self, x1: int, y1: int, x2: int, y2: int) -> None:
            int tmp
            if (x1 > x2) {
            tmp = x1
            x1 = x2
            x2 = tmp


    def set_real_coordinates(self, x1: int, y1: int, x2: int, y2: int) -> None:
            set_real_coordinates_no_inform(x1, y1, x2, y2)
            _real_coords->in_world_map = TERRAIN_MAP_WORLD_MAP.add_terrain(base_name(self),
            _real_coords->x1, _real_coords->y1,
            _real_coords->x2, _real_coords->y2)


    def set_real_offsets(self, xoff: int, yoff: int, zoff: int) -> None:
            _real_coords = new(class real_coords)
            _real_coords->xdiff = xoff
            _real_coords->ydiff = yoff
            _real_coords->xydiff = to_int(sqrt(to_float(_real_coords->xdiff) * to_float(_real_coords->xdiff)+
            to_float(_real_coords->ydiff) * to_float(_real_coords->ydiff)))


    def set_newline_mode(self, mode: int) -> None:
            {
            _newline_mode = mode


    def set_visible_distance(self, distance: int) -> None:
            _visible_distance = distance


    def query_visible_distance(self, ) -> int:
            return _visible_distance


    def __init__(self):


    def setup_area_map(self, ) -> None:
            {
            int   index
            load_area_map()
            load_zone_map()
            if (!arrayp(_room_map)) {
            _room_map = [})
            for (index = 0; index < _width; index++)
            _room_map += [allocate(_width)]


    def query_feature_ob(self, name: str) -> MudObject:
            return _features[name]->feature_ob


    def add_signposts(self, room: MudObject) -> None:
            {
            class sign_data sign
            int     *coords = room.query_terrain_coords()
            int     x = coords[0]
            int     y = coords[1]
            string  title = sprintf("%d:%d", x, y)
            object  sign_ob
            sign = _signposts[title]
            if (!sign) {
            return


    def setup_zones(self, room: MudObject) -> None:
            {
            string  *zones
            int     *coords = room.query_terrain_coords()
            int     x = coords[0]
            int     y = coords[1]
            string  type
            string  zone
            if (!sizeof(_zone_map)) {
            return


    def calc_random_descs(self, room: MudObject, key: str) -> None:
            {
            int      limit = _random_desc_limit
            int      *indices = [})
            int      *coords = room.query_terrain_coords()
            int      seed = (coords[0] * 2) + coords[1]
            mapping  desc
            mixed    *descs = _random_descs[key]
            int      index
            if (limit > sizeof(descs)) {
            limit = sizeof(descs)


    def calc_random_chats(self, room: MudObject, key: str) -> None:
            {


    def query_dest_coordinate_string(self, x: int, y: int, z: int, direc: str, key: str) -> str:
            class char_map_data  room_setup
            room_setup = query_char_map(x, y)
            if (room_setup->type == AREA_WORLD) {
            return room_setup->path.query_dest_coordinate_string(x, y, z, direc, key)


    def query_ground_room_co_ords(self, x: int, y: int) -> List[int]:
            class char_map_data  room_setup
            room_setup = query_char_map(x, y)
            return [x, y, room_setup->height]


    def query_ground_room(self, x: int, y: int) -> str:
            int* co_ords
            co_ords = query_ground_room_co_ords(x, y)
            return base_name(self) + ":" + co_ords[0] + ":" + co_ords[1] + ":" + co_ords[2]


    def query_climb_base_room(self, x: int, y: int, z: int, map_room: int, ref: str) -> str:
            class char_map_data  room_setup
            string *tmp
            room_setup = query_char_map(x, y)
            if (!room_setup) {
            return 0


    def query_base_room(self, x: int, y: int, z: int, map_room: int) -> str:
            string dest
            dest = "bing"
            return query_climb_base_room(x, y, z, map_room, ref dest)


    def setup_room(self, room: MudObject, base_path: str) -> None:
            {
            string main_base
            string base
            int      *room_coords = room.query_terrain_coords()
            mixed    *coords
            int      x
            int      y
            string   direc
            class char_map_data  room_setup
            string*  dirs
            mapping  adjacent_descs = ([ ])
            mapping  adjacent_sent = ([ ])
            mapping  distant
            string   adjacent
            string   key
            string   room_long = ""
            string   key_here
            mixed    *exit_mods
            object   new_room
            string   outside_types = ""
            mixed    *exits
            mapping  exit
            string   *sentances
            mixed   tmp
            int z
            int road_jump
            class coord fluff
            string* miss_road
            mapping ignore_exits
            string  walk_pre
            string  walk_full
            string  journey_pre
            string  new_base_path
            if (!arrayp(room_coords)) {
            debug_printf("Unable to find room coordinates from %O\n", file_name(room))
            return


    def find_adjacent_terrain(self, x: int, y: int) -> str:
            {
            string index
            class coord real
            if (!_real_coords || !_real_coords->in_world_map) {
            return 0


    def find_all_adjacent_terrains(self, ) -> None:
            find_adjacent_terrain(-1,-1)
            find_adjacent_terrain(-1,0)
            find_adjacent_terrain(-1,40)
            find_adjacent_terrain(0,40)
            find_adjacent_terrain(40,40)
            find_adjacent_terrain(40,0)
            find_adjacent_terrain(40,-1)
            find_adjacent_terrain(0,-1)


    def add_room_to_zone(self, room: MudObject, zone: str) -> None:
            {
            object *zones = _room_zones[zone]
            if (!zones)
            zones = [room]
            else if (zones.index(room) if room in zones else -1 == -1)
            zones += [room]
            _room_zones[zone] = zones - [0]


    def query_room(self, x: int, y: int, z: int) -> Any:
            {
            class char_map_data room_map = query_char_map(x, y)
            string base_path
            object room
            class coord real
            base_path = query_base_room(x, y, z, TERRAIN_MAP_ROOM_EXACT)
            if (!base_path) {
            return 0


    def query_room_at(self, x: int, y: int, z: int) -> MudObject:
            {
            if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
            return 0
            return find_object(sprintf("%s:%d:%d:%d", base_name(self), x, y, z))


    def load_room_at(self, x: int, y: int, z: int) -> MudObject:
            {
            class char_map_data room_map = query_char_map(x, y)
            if (!room_map) {
            debug_printf("Unable to load room at %d %d\n", x, y)
            return 0


    def query_debug_map(self, x: int, y: int, width: int, showx: int, showy: int) -> str:
            int i
            int j
            int sx
            int sy
            int ny
            string ret
            string base
            string new_base
            string colour
            ret = ""
            sx = x - width / 2
            sy = y + width / 2
            for (j = 0; j < width; j++) {
            if (sy - j >= 0 && sy - j < _height) {
            for (i = 0; i < width; i++) {
            if (sx + i >= 0 && sx + i < _width) {
            if (sx +i == showx && sy - j == showy) {
            ret += "%^YELLOW%^" + _area_map[sy - j][sx + i..sx + i] +
            "%^RESET%^"
            colour = 0
            } else {
            if (colour) {
            ret += "%^RESET%^"
            colour = 0


    def query_debug_map_char(self, x: int, y: int) -> str:
            return _area_map[y][x..x]


    def query_debug_map_feature(self, name: str) -> str:
            int x
            int y
            class feature_data feature
            mixed data
            string ret
            int colour
            int found
            feature = _features[name]
            ret = ""
            colour = 0
            for (y = _height - 1; y >= 0; y--) {
            for (x = 0; x < _width; x++) {
            data = feature->feature_ob.query_feature_desc_from(x, y, 0, 1)
            found = sizeof(data)
            if (found) {
            if (!colour) {
            ret += "%^YELLOW%^"
            colour = 1


    def query_debug_map_feature_distant(self, feature: str) -> str:
            int x
            int y
            mixed data
            string ret
            int colour
            class coord fluff
            ret = ""
            colour = 0
            for (y = _height - 1; y >= 0; y--) {
            for (x = 0; x < _width; x++) {
            fluff = query_real_from_terrain_coord(x, y, 0)
            data = feature.query_feature_desc_from(fluff->x, fluff->y, fluff->z)
            if (data && sizeof(data)) {
            if (!colour) {
            ret += "%^YELLOW%^"
            colour = 1


    def query_player_map(self, x_c: int, y_c: int, z_c: int, visibility: int) -> str:
            string ret, item, base, current, *keys
            mixed *map, *colours
            mapping data, key, colour_key
            int i, j
            int distance
            distance = _visible_distance * visibility / 100
            if (!distance) {
            distance = 1


    def get_an_outside_chat(self, types: str) -> str:
            {
            class char_map_data   item
            string    *chats = [})
            int       index
            mixed     *item_chats
            for (index = 0; index < sizeof(types); index++) {
            item = _char_map[types[index..index]]
            if (!item) {
            continue


    def add_room_type(self, type: str, base_path: str) -> None:
            {
            _char_map[type] = new(class char_map_data,
            type: AREA_ROOM, path:base_path)


    def set_random_desc_limit(self, new_limit: int) -> None:
            {
            _random_desc_limit = new_limit


    def set_random_chat_limit(self, new_limit: int) -> None:
            {
            _random_chat_limit = new_limit


    def add_random_desc(self, types: str, description: str, items: Any, item_desc: Any) -> None:
            {
            int   index
            for (index = 0; index < sizeof(types); index++) {
            if (!_random_descs[types[index..index]])
            _random_descs[types[index..index]] = [})
            _random_descs[types[index..index]] += [([ "desc": description,
            "items":items, "item_desc":item_desc ])]


    def add_random_chat(self, types: str, chats: str) -> None:
            {
            int   index
            for (index = 0; index < sizeof(types); index++) {
            if (!_random_chats[types[index..index]])
            _random_chats[types[index..index]] = [})
            _random_chats[types[index..index]] += chats


    def set_external_chats(self, type: str, chats: Any) -> None:
            {
            if (!_char_map[type]) {
            return


    def add_feature_ob(self, title: str, feature: MudObject) -> None:
            if (_real_coords && _real_coords->xdiff) {
            feature.set_distance_multiplier(_real_coords->xdiff)


    def set_feature_chats(self, title: str, chats: Any, night_chats: Any) -> None:
            {
            if (!_features[title]) {
            return


    def remove_feature(self, title: str) -> None:
            {
            object room
            if (!_features[title]) {
            return


    def add_zones(self, type: str, zone_names: str) -> None:
            {
            _zone_types[type] = zone_names


    def reset_handler(self, ) -> None:
            {
            mixed *rooms
            if (arrayp(_room_map)) {
            foreach(rooms in _room_map) {
            rooms.dest_me()


    def load_zone_map(self, ) -> None:
            {
            string   map_path = query_map_file() + ".zones"
            int      index = 1
            string   line
            int      width
            int      height
            _zone_map = [})
            while (line = read_file(map_path, index++, 1)) {
            if (width < sizeof(line))
            width = sizeof(line)
            _zone_map += [line]


    def load_area_map(self, ) -> None:
            {
            string   map_path = query_map_file() + ".map"
            int      index = 1
            int      height
            string   line
            _area_map = [})
            while (line = read_file(map_path, index++, 1)) {
            if (sizeof(line)) {
            line = line[0..<2]
            if (_width < sizeof(line)) {
            _width = sizeof(line)


    def create_virtual_object(self, x_str: str, y_str: str, z_str: str) -> MudObject:
            {
            int x = to_int(x_str)
            int y = to_int(y_str)
            int z = to_int(z_str)
            if (!stringp(x_str) || !stringp(y_str) || !stringp(z_str)) {
            return 0


    def find_room_at_real_coord(self, x: int, y: int, z: int) -> str:
            class char_map_data room_map
            class coord our
            our = query_terrain_from_real_coord(x, y, z)
            if (!our) {
            return 0


    def query_direction_distance(self, dir: str) -> int:
            switch (_direcs[dir][3]) {
            case X_DIFF :
            return _real_coords->xdiff
            case Y_DIFF :
            return _real_coords->ydiff
            case XY_DIFF :
            return _real_coords->xydiff


    def dest_me(self, ) -> None:
            class feature_data womble
            string name
            foreach (name, womble in _features) {
            if (womble->feature_ob) {
            womble->feature_ob.dest_me()



class Handler_base(MudObject):
