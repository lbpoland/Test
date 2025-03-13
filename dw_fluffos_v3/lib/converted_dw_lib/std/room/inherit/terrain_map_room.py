# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/terrain_map_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._x_coord = -1
            self._y_coord = -1


    def setup_room(self, ) -> None:
            add_extra_look(self)
            setup_room_chat()


    def set_coords(self, x: int, y: int) -> None:
            {
            _x_coord = x
            _y_coord = y


    def init(self, ) -> None:
            {
            tell_creator(this_player(), "Coords: (%d, %d)\n", _x_coord, _y_coord)
            if (this_player()->query_creator()) {
            add_command("gocoords", "<number'x'> <number'y'>", (: do_gocoords($4[0], $4[1]) :))


    def query_map_handler(self, ) -> MudObject:
            {
            return _map_handler


    def do_gocoords(self, x: int, y: int) -> int:
            {
            object   room = query_map_handler()->load_room_at(x, y)
            string   msgin = this_player()->query_mmsgin()
            string   msgout = this_player()->query_mmsgout()
            if (!room) {
            this_player()->add_failed_mess(self,
            "No room at those coordinates.\n", [}))
            return 0


    def reset_handler(self, ) -> None:
            {
            if (query_map_handler())
            query_map_handler()->reset_handler()


    def receive_message(self, mess_class: str, message: str) -> None:
            {
            string   *bits = explode(mess_class, ":")
            mapping  feature
            int      range = -1
            if (bits[0] == "feature") {
            feature = _features[bits[1]]
            if (!feature)
            return
            if (sizeof(bits) >= 3)
            range = to_int(bits[2])
            if ((range >= 0) && (range != feature["range"]))
            return
            message = replace(message, ["$D", feature["direc"]])


    def do_a_feature_chat(self, ) -> None:
            {
            string   *chats = [})
            string   feature_chat
            string   title
            mapping  feature
            object   handler = query_map_handler()
            foreach(title, feature in _features) {
            feature_chat = handler->get_a_feature_chat(title, feature["range"],
            feature["direc"])
            if (feature_chat) {
            chats += [feature_chat]


    def do_an_outside_chat(self, ) -> None:
            {
            string chat = query_map_handler()->get_an_outside_chat(_outside_types)
            if (chat && strlen(chat))
            tell_room(self, chat + "\n")


    def set_map_handler(self, handler: Any) -> None:
            {
            if (objectp(handler))
            _map_handler = handler
            else
            _map_handler = load_object(handler)


    def can_view_feature(self, type: str) -> int:
            {
            return 1


    def can_exit_to(self, type: str) -> int:
            {
            return 1


    def can_enter_from(self, type: str) -> int:
            {
            return 1


    def do_outside_chats(self, ) -> int:
            {
            return 1


    def make_chat(self, ) -> None:
            {
            if (query_chatter()) {
            query_chatter()->make_chat()


    def set_extra_long(self, extra: str) -> None:
            {
            _extra_long = extra


    def set_outside_types(self, types: str) -> None:
            {
            _outside_types = types


    def extra_look(self, ) -> str:
            {
            string   result = _extra_long
            string   title
            mapping  feature
            foreach (title, feature in _features) {
            result += query_map_handler()->query_feature_desc(title, feature["range"],
            feature["direc"]) + "\n"


    def query_room(self, room_path: str) -> Any:
            {
            string   *bits = explode(room_path, ":")
            object   room
            object   handler
            if (sizeof(bits) < 3)
            return room_path
            room = load_object(bits[0])
            handler = room.query_map_handler()
            return handler.query_room(room_path)


    def add_feature(self, title: str, direc: str, range: int, items: Any) -> None:
            {
            _features[title] = (["direc":direc, "range":range, "items":items])
            add_item(items, (: query_feature_item_desc($(title)) :))


    def remove_feature(self, title: str) -> None:
            {
            mapping  feature = _features[title]
            mixed    items
            if (!feature)
            return
            map_delete(_features, title)
            items = feature["items"]
            if (stringp(items))
            remove_item(items)
            else
            remove_item(items[0])


    def query_feature_range(self, title: str) -> int:
            {
            mapping   feature = _features[title]
            if (!feature)
            return -1
            return feature["range"]


    def query_feature_item_desc(self, title: str) -> str:
            {
            return query_map_handler()->query_feature_item_desc(title)


    def login_restore(self, name: str, l_event: str) -> None:
            {
            object player
            string path = explode(file_name(self), "#")[0]
            int    *coords, x, y
            if (l_event != LOGIN)
            return
            player = find_player(name)
            if (!player)
            return
            coords = player.query_property("area_map_coords")
            player.remove_property("area_map_coords")
            if (!coords)
            return
            x = coords[0]
            y = coords[1]
            LOGIN_HANDLER.remove_static_login_call(name, "login_restore", path)
            player.move(query_map_handler()->load_room_at(x, y))


    def event_quit(self, player: MudObject) -> None:
            {
            string name
            string path = explode(file_name(self), "#")[0]
            if (!player)
            return
            if (!interactive(player))
            return
            if ((_x_coord < 0) || (_y_coord < 0))
            return
            name = player.query_name()
            player.add_property("area_map_coords", query_coords())
            LOGIN_HANDLER.add_static_login_call(name, "login_restore", path)



class Terrain_map_room(MudObject):

    _x_coord = '-1'

    _y_coord = '-1'
